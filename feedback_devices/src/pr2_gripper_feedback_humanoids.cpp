#include "ros/ros.h"
#include "feedback_devices/tacta_hydra.h"
#include "pr2_controllers_msgs/JointControllerState.h"
#include "pr2_msgs/PressureState.h"
#include <iostream>
#include <fstream>

//======================== DEFINED CONSTANTS ==================================

//Robot Specific Constants
#define HANDS 2
#define FINGERS 2
#define SENSORS 22

//Fingertip Sensor Specific Constants
#define SENSOR_START 7
#define RAW_TO_NEWT 1600 //Determined from PR2 Code and NOT VERIFIED
#define MAX_FORCE_NEWT 15
#define FMIN .25
#define CRUSH_LIMIT .1

//Kuchenbecker Constatns
#define FLIMIT .75 //Newtons that defines contact
#define TOUCH_READINGS 1 //Number of readings to take immediately after touching an object

#define CALIBRATION_READINGS 3
#define FREQ_THRESHOLD 75

//======================== TYPE DEFINES AND ENUMS =============================

enum hand_t {LEFT_HAND, RIGHT_HAND};
enum finger_t {LEFT_FINGER, RIGHT_FINGER};
enum state_t {UNCALIBRATED, OPEN, TOUCH, LOAD, CRUSH};

//======================== FUNCTION PROTOTYPES ================================

void r_gripper_pressure_cb(pr2_msgs::PressureState input);
void l_gripper_pressure_cb(pr2_msgs::PressureState input);
void calculate_pressure(pr2_msgs::PressureState input, hand_t hand);

void r_gripper_state_cb(pr2_controllers_msgs::JointControllerState input);
void l_gripper_state_cb(pr2_controllers_msgs::JointControllerState input);
void calculate_gripper_state(pr2_controllers_msgs::JointControllerState input, hand_t hand);

bool detect_slip(hand_t hand);

void printPressureLog(int hand);

//======================== GLOBAL ARRAYS ======================================

int state[HANDS] = {UNCALIBRATED};
int state_prev[HANDS] = {UNCALIBRATED};
int gripper[HANDS] = {0};

int hardness[HANDS] = {0};
int touch_num[HANDS] = {0};

int current_value[HANDS][FINGERS][SENSORS] = {{{0}}};
int prev_current_value[HANDS][FINGERS][SENSORS] = {{{0}}};

int calibration_value[HANDS][FINGERS][SENSORS] = {{{0}}};
int calibration_sum[HANDS][FINGERS][SENSORS] = {{{0}}};
int calibration_count[HANDS] = {0};

ros::Publisher pub_tacta_hydra;
//feedback_devices::tacta_pr2_grippers grippers;
feedback_devices::tacta_hydra hydra;

//======================== FUNCTIONS ==========================================

void r_gripper_state_cb(pr2_controllers_msgs::JointControllerState input){

    calculate_gripper_state(input, RIGHT_HAND);

}

void l_gripper_state_cb(pr2_controllers_msgs::JointControllerState input){

    calculate_gripper_state(input, LEFT_HAND);

}

void calculate_gripper_state(pr2_controllers_msgs::JointControllerState input, hand_t hand){

    //Check what state the hand is in
    if (state[hand] == TOUCH || state[hand] == LOAD) {

        //Check if we already have a value
        if (gripper[hand] == 0) gripper[hand] = input.process_value;

        //Check to make sure the difference between the two isn't too large
        if ((gripper[hand] - input.process_value) > CRUSH_LIMIT) {
            state_prev[hand] = state[hand];
            state[hand] = CRUSH;
        }
        else if ((gripper[hand] - input.process_value) <= CRUSH_LIMIT) state[hand] = state_prev[hand];
    }

}

void r_gripper_pressure_cb(pr2_msgs::PressureState input){

    calculate_pressure(input, RIGHT_HAND);
}


void l_gripper_pressure_cb(pr2_msgs::PressureState input){

    calculate_pressure(input, LEFT_HAND);
}

void calculate_pressure(pr2_msgs::PressureState input, hand_t hand){

    int rf_adc = 0;
    int lf_adc = 0;

    //Remove the calibration value and calculate the overal pressure
    for (int sensor = SENSOR_START; sensor < SENSORS; sensor++){

        //Remove the calibration value
        current_value[hand][LEFT_FINGER][sensor] = input.l_finger_tip[sensor] - calibration_value[hand][LEFT_FINGER][sensor];
        current_value[hand][RIGHT_FINGER][sensor] = input.r_finger_tip[sensor] - calibration_value[hand][RIGHT_FINGER][sensor];

        //Make sure the values don't go negative
        if (current_value[hand][LEFT_FINGER][sensor] < 0) current_value[hand][LEFT_FINGER][sensor] = 0;
        if (current_value[hand][RIGHT_FINGER][sensor] < 0) current_value[hand][RIGHT_FINGER][sensor] = 0;

        //Sum the pressure
        rf_adc += current_value[hand][LEFT_FINGER][sensor];
        lf_adc += current_value[hand][RIGHT_FINGER][sensor];

        //Sum the pressure
        rf_adc += current_value[hand][LEFT_FINGER][sensor];
        lf_adc += current_value[hand][RIGHT_FINGER][sensor];
    }

    int right_newton = rf_adc / RAW_TO_NEWT;
    int left_newton = lf_adc / RAW_TO_NEWT;
    int total_newton = .5 * (right_newton + left_newton);

    if (total_newton > MAX_FORCE_NEWT) total_newton = MAX_FORCE_NEWT;




    //If the state of the hand is OPEN
    if (state[hand] == OPEN) {

        hydra.amp[hand] = 0;
        hydra.freq[hand] = feedback_devices::tacta_hydra::FREQ_ON;

        if (left_newton >= FLIMIT && right_newton >= FLIMIT) state[hand] = TOUCH;
    }



    //If the state of the hand is TOUCH
    if (state[hand] == TOUCH) {

        //Increment the number of times we've touched the object
        touch_num[hand]++;

        //Calculate the max force seen during this time
        if (total_newton > hardness[hand]) hardness[hand] = total_newton;

        //If we have touched the object enough times, move to the next state
        if (touch_num[hand] > TOUCH_READINGS) state[hand] = LOAD;

        //TODO Make sure that this doesn't cause problems!
        if (right_newton < FMIN || left_newton < FMIN) {
            touch_num[hand] = 0;
            hardness[hand] = 0;
            gripper[hand] = 0;
            state[hand] = OPEN;
        }

    }



    //If the gripper has been rh_calibrated then this code can just be run normally
    if (state[hand] == LOAD) {

        hydra.amp[hand] = (total_newton / MAX_FORCE_NEWT) * 255;

        if(detect_slip(hand)){ //Slip is Occuring

            hydra.freq[hand] = feedback_devices::tacta_hydra::FREQ_SLIP;

        } else { //Slip is not Occuring

            hydra.freq[hand] = feedback_devices::tacta_hydra::FREQ_ON;

        }

        //Save the current state as the previous current state
        for (int sensor = SENSOR_START; sensor < SENSORS; sensor++){
            prev_current_value[hand][LEFT_FINGER][sensor] = current_value[hand][LEFT_FINGER][sensor];
            prev_current_value[hand][RIGHT_FINGER][sensor] = current_value[hand][RIGHT_FINGER][sensor];
        }

        //TODO Make sure that this doesn't cause problems!
        if (right_newton < FMIN || left_newton < FMIN) {

            //Save the current state as the previous current state
            for (int sensor = SENSOR_START; sensor < SENSORS; sensor++){
                prev_current_value[hand][LEFT_FINGER][sensor] = 0;
                prev_current_value[hand][RIGHT_FINGER][sensor] = 0;
            }

            gripper[hand] = 0;
            state[hand] = OPEN;
        }

    } //End State == LOAD


    if (state[hand] == CRUSH) {

        hydra.amp[hand] = 255;
        hydra.freq[hand] = feedback_devices::tacta_hydra::FREQ_CRUSH;

    }


    if (state[hand] == UNCALIBRATED) {

        // We're calibrating by taking the average of the sensor data, this will sum them
        for (int sensor = SENSOR_START; sensor < SENSORS; sensor++){
            calibration_sum[hand][LEFT_FINGER][sensor] += input.l_finger_tip[sensor];
            calibration_sum[hand][RIGHT_FINGER][sensor] += input.r_finger_tip[sensor];
        }

        calibration_count[hand]++;

        if ( calibration_count[hand] >= CALIBRATION_READINGS){
            for (int sensor = SENSOR_START; sensor < SENSORS; sensor++){
                calibration_value[hand][LEFT_FINGER][sensor] = calibration_sum[hand][LEFT_FINGER][sensor] / calibration_count[hand];
                calibration_value[hand][RIGHT_FINGER][sensor] = calibration_sum[hand][RIGHT_FINGER][sensor] / calibration_count[hand];
            }
            state[hand] = OPEN;
        }
    }

}


bool detect_slip(hand_t hand){

    int min = 30000, max = -30000;

    for (int sensor = SENSOR_START; sensor < SENSORS; sensor++){

        int l_deriv = current_value[hand][LEFT_FINGER][sensor] - prev_current_value[hand][LEFT_FINGER][sensor];
        int r_deriv = current_value[hand][RIGHT_FINGER][sensor] - prev_current_value[hand][RIGHT_FINGER][sensor];

        if (l_deriv < min) min = l_deriv;
        if (l_deriv > max) max = l_deriv;

        if (r_deriv < min) min = r_deriv;
        if (r_deriv > max) max = r_deriv;

    }

    //Determine the output

    //If both of the numbers are within the noise range don't do anything
    if (abs(min) < FREQ_THRESHOLD && abs(max) < FREQ_THRESHOLD) return false;

    //If the numbers have different signs, return that we're slipping
    if ((min < 0 && abs(min) > FREQ_THRESHOLD) && (max > 0 && abs(max) > FREQ_THRESHOLD)) return true;

    //Else return that we're not slipping
    return false;

}

//std::ofstream rh_rf_data, rh_lf_data, rh_rf_der, rh_lf_der;
//std::ofstream lh_rf_data, lh_lf_data, lh_rf_der, lh_lf_der;
//int rh_count = 0, lh_count = 0;
//void printPressureLog(int hand){

//    if (hand == RIGHT){

//        if (rh_count == 0){
//            rh_rf_data.open ("rh_rf_pressure.csv");
//            rh_lf_data.open ("rh_lf_pressure.csv");
//            rh_rf_der.open("rh_rf_derivative.csv");
//            rh_lf_der.open("rh_lf_derivative.csv");
//        }

//        for (int i = 0; i < SENSORS; i++){

//            rh_rf_data << rh_rf_current[i] << ",";
//            rh_lf_data << rh_lf_current[i] << ",";
//            rh_rf_der << rh_rf_deriv[i] << ",";
//            rh_lf_der << rh_lf_deriv[i] << ",";

//        }

//        rh_count++;
//        rh_rf_data << "\n";
//        rh_lf_data << "\n";
//        rh_rf_der << "\n";
//        rh_lf_der << "\n";

//    } else {

//        if (lh_count == 0){
//            lh_rf_data.open ("lh_rf_pressure.csv");
//            lh_lf_data.open ("lh_lf_pressure.csv");
//            lh_rf_der.open("lh_rf_derivative.csv");
//            lh_lf_der.open("lh_lf_derivative.csv");
//        }

//        for (int i = 0; i < SENSORS; i++){

//            lh_rf_data << lh_rf_current[i] << ",";
//            lh_lf_data << lh_lf_current[i] << ",";
//            lh_rf_der << lh_rf_deriv[i] << ",";
//            lh_lf_der << lh_lf_deriv[i] << ",";

//        }

//        lh_count++;
//        lh_rf_data << "\n";
//        lh_lf_data << "\n";
//        lh_rf_der << "\n";
//        lh_lf_der << "\n";


//    }
//}

void send_feedback(){
    pub_tacta_hydra.publish(hydra);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "pr2_grippers_humanoids");

  //Setup everything for the publishes
  ros::NodeHandle nh;

  //Advertise the two publishers, one for the commands and one for the gui
  pub_tacta_hydra = nh.advertise<feedback_devices::tacta_hydra>("/feedback_devices/tacta_hydra/input", 1);

  //Create all the subscribers that are needed
  ros::Subscriber sub_r_gripper_state = nh.subscribe("/r_gripper_controller/state",1, r_gripper_state_cb);
  ros::Subscriber sub_l_gripper_state = nh.subscribe("/l_gripper_controller/state",1, l_gripper_state_cb);
  ros::Subscriber sub_r_gripper_pressure = nh.subscribe("/pressure/r_gripper_motor", 1, r_gripper_pressure_cb);
  ros::Subscriber sub_l_gripper_pressure = nh.subscribe("/pressure/l_gripper_motor", 1, l_gripper_pressure_cb);

  hydra.freq[LEFT_HAND] = feedback_devices::tacta_hydra::FREQ_OFF;
  hydra.freq[RIGHT_HAND] = feedback_devices::tacta_hydra::FREQ_OFF;

  ros::Rate r(10);

  while(ros::ok()){
      send_feedback();
      ros::spinOnce();
      r.sleep();
  }

  //Spin Forever
  ros::spin();

  return 0;

}
