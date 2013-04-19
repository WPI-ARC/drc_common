/*
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include <ros/ros.h>
#include <math.h>
#include <string>
#include <interactive_markers/menu_handler.h>
#include <interactive_markers/interactive_marker_server.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <resource_retriever/retriever.h>

#include "gui/updateValvePos.h"

#define PI 3.14159
#define KG_RANGE .005

using namespace visualization_msgs;
using namespace interactive_markers;

void makeValve(geometry_msgs::Pose newPose);

ros::ServiceClient valve_request_client;
ros::ServiceClient valve_update_client;

// Wheel Radius Starts is 10" center to center, 11" side to side
float marker_size = .0254;
interactive_markers::MenuHandler menu_handler;
interactive_markers::InteractiveMarkerServer * server = NULL;

geometry_msgs::Pose defaultPose;
float u1_default = .955968;
float u2_default = .966842;
float u3_default = 1;

void processFeedback( const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback ){

	switch (feedback->event_type){
		
		case visualization_msgs::InteractiveMarkerFeedback::MENU_SELECT:

      //Set the position to where the valve current is
      geometry_msgs::Pose newPose;
      newPose = feedback->pose;

       gui::updateValvePos valve_request;
       valve_request.request.valve.header = feedback->header;
       valve_request.request.valve.pose = feedback->pose;
       valve_request.request.radius = 10 * marker_size / 2;;

       gui::updateValvePos valve_update;
       valve_update.request.valve.header = feedback->header;
       valve_update.request.valve.pose = feedback->pose;
       valve_update.request.radius = .254 / 2;
       valve_update.request.id = "KG-EX";

      switch(feedback->menu_entry_id){

        case 1:
           if (valve_request_client.call(valve_request)) { 
             newPose = valve_request.response.valve.pose;
           }
           else { ROS_ERROR("/gui/valve_interact_test.cpp: Pointcloud Request FAILED"); }
           break;
        case 2:
           if (valve_update_client.call(valve_update)) { 
            ROS_INFO("%s", valve_update.response.success_code.c_str()); }
           else { ROS_ERROR("/gui/valve_interact_test.cpp: Ben or Calder FAILED"); }
           break;

        //This entire ugly set of switch cases just handles re-sizing the valve
			  case 4: marker_size *= .50; break;
				case 5: marker_size *= .60; break;
				case 6: marker_size *= .70; break;
				case 7: marker_size *= .80; break;
				case 8: marker_size *= .90; break;
				
				case 9: marker_size = .0254; break;
				
				case 10: marker_size *= 1.1; break;
				case 11: marker_size *= 1.2; break;
				case 12: marker_size *= 1.3; break;
				case 13: marker_size *= 1.4; break;
				case 14: marker_size *= 1.5; break;
			} //END switch(feedback->menu_entry_id){
		
		  server->erase("valve");
			makeValve(newPose);
			
			break;
	} //END switch (feedback->event_type){

  server->applyChanges();
}

void processFeedbackTESTING( const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback ){

	switch (feedback->event_type){
		
		case visualization_msgs::InteractiveMarkerFeedback::MENU_SELECT:

      //Set the position to where the valve current is
      geometry_msgs::Pose newPose;
      geometry_msgs::Pose testPose;
      newPose = feedback->pose;

      gui::updateValvePos valve_request;
      valve_request.request.valve.header = feedback->header;
      valve_request.request.radius = 10 * marker_size / 2;;

      gui::updateValvePos valve_update;
      valve_update.request.valve.header = feedback->header;
      valve_update.request.radius = .254 / 2;

     int tests = 0;

      float x_d = 0;
      float y_d = 0;
      float z_d = 0;

      float u1 = 0;
      float u2 = 0;
      float u3 = 0;

      float initial_dot_product = 0;
      float initial_position_distance = 0;
      float initial_orientation_distance = 0;
      float initial_pose_distance = 0;

      float final_dot_product = 0;
      float final_position_distance = 0;
      float final_orientation_distance = 0;
      float final_pose_distance = 0;

      //Variables from Parameters
      //ros::param::get(key, val);
      bool cause_translations;
      ros::param::get("/gui/valve_interact/cause_translations", cause_translations);
      bool cause_rotations;
      ros::param::get("/gui/valve_interact/cause_rotations", cause_rotations);
      int test_iterations;
      ros::param::get("/gui/valve_interact/test_iterations", test_iterations);
      int max_rotation_deg;
      ros::param::get("/gui/valve_interact/max_rotation_deg", max_rotation_deg);
      float max_rotation_rad = max_rotation_deg * 0.0174532925;

      int max_translation_mm;
      ros::param::get("/gui/valve_interact/max_translation_mm", max_translation_mm);
      int DTW_max_good_translation_err_mm;
      ros::param::get("/gui/valve_interact/DTW_max_good_translation_err_mm", DTW_max_good_translation_err_mm);
      int DTW_max_good_rotation_err_deg;
      ros::param::get("/gui/valve_interact/DTW_max_good_rotational_err_deg", DTW_max_good_rotation_err_deg);
      float DTW_max_good_rotation_err_rad = DTW_max_good_rotation_err_deg * 0.0174532925;

      std::string DTW_good_id;
      ros::param::get("/gui/valve_interact/DTW_good_id", DTW_good_id);
      std::string DTW_bad_id;
      ros::param::get("/gui/valve_interact/DTW_bad_id", DTW_bad_id);
      bool use_valve_icp;
      ros::param::get("/gui/valve_interact/use_valve_icp", use_valve_icp);
      bool send_2_robot;
      ros::param::get("/gui/valve_interact/send_2_robot", send_2_robot);
      bool print_debug;
      ros::param::get("/gui/valve_interact/print_debug", print_debug);
      int test_delay_display_sec;
      ros::param::get("/gui/valve_interact/test_display_delay_sec", test_delay_display_sec);
      bool use_valve_icp_answer;
      ros::param::get("/gui/valve_interact/use_valve_icp_answer", use_valve_icp_answer);

      switch(feedback->menu_entry_id){

        case 15: //Set New Default
          defaultPose = feedback->pose;
          break;
          
        case 16: //Move to Default
            server->erase("valve");
			      makeValve(defaultPose);
            server->applyChanges();
          break;
          
        case 17: //The new COMPLETE tester

          if(print_debug) {ROS_INFO("Printing Debug Information: ");
            ROS_INFO("============================================");
            
            if (defaultPose.position.x != .5 && defaultPose.position.y != 0 && defaultPose.position.z != .5){
              ROS_INFO("Default POSE has been set to: (%f, %f, %f) [%f, %f, %f, %f]", defaultPose.position.x,
                                                                                      defaultPose.position.y,
                                                                                      defaultPose.position.z,
                                                                                      defaultPose.orientation.w,
                                                                                      defaultPose.orientation.x,
                                                                                      defaultPose.orientation.y,
                                                                                      defaultPose.orientation.z);
            } else {ROS_INFO(" *** WARNING *** Default Pose is NOT Set Proceed with CAUTION ");}

            ROS_INFO("Test Iterations: %d", test_iterations);
            
            if(use_valve_icp) {ROS_INFO("Running ICP: True");}
              else{ROS_INFO("Running ICP: False");}

            if(send_2_robot) {ROS_INFO("Sending Pose 2 Robot: True");}
              else{ROS_INFO("Sending Pose 2 Robot: False");}

            if(cause_translations) {ROS_INFO("Cause translations: True");}
              else{ROS_INFO("Cause translations: False");}
            
            ROS_INFO("Max Translation (mm): %d", max_translation_mm);

            if(cause_rotations) {ROS_INFO("Cause Rotations: True");}
              else{ROS_INFO("Cause Rotations: False");}

            ROS_INFO("Max Rotation (deg): %d", max_rotation_deg);

            ROS_INFO("Dynamic Time Warping Parameters:");
            ROS_INFO("  Max \"GooD\" Translation Error (mm): %d", DTW_max_good_translation_err_mm);
            ROS_INFO("  Max \"GooD\" Rotation Error (deg): %d", DTW_max_good_rotation_err_deg);
            ROS_INFO("  \"GooD\" String ID: %s", DTW_good_id.c_str());
            ROS_INFO("  \"BaD\" String ID: %s", DTW_bad_id.c_str());
            ROS_INFO("============================================");

            

          } else { ROS_INFO("Not Printing Debug information");
                   ROS_INFO("============================================");}

          while(tests < test_iterations){

            testPose = defaultPose;
            
            if (cause_translations){

              x_d = 0.0;
              y_d = 0.0;
              z_d = 0.0;

              x_d = ((float)(std::rand() % max_translation_mm)/1000) - ((max_translation_mm / 2) / 1000);
              y_d = ((float)(std::rand() % max_translation_mm)/1000) - ((max_translation_mm / 2) / 1000);
              z_d = ((float)(std::rand() % max_translation_mm)/1000) - ((max_translation_mm / 2) / 1000);
              testPose.position.x += x_d;
              testPose.position.y += y_d;
              testPose.position.z += z_d;

              initial_position_distance = 0.0;
              initial_position_distance = sqrt(pow(defaultPose.position.x - testPose.position.x, 2) +
                                       pow(defaultPose.position.y - testPose.position.y, 2) +
                                       pow(defaultPose.position.z - testPose.position.z, 2));

            }
            
            if(cause_rotations) {
            
              initial_orientation_distance = 100;

              while (initial_orientation_distance > max_rotation_rad) {

                u1 = 0.0;
                u2 = 0.0;
                u3 = 0.0;
  
                u1 = ((float)(std::rand() % 100)/100);
                u2 = ((float)(std::rand() % 100)/100);
                u3 = ((float)(std::rand() % 100)/100);
                testPose.orientation.w = std::sqrt(1 - u1)*std::sin(2 * PI * u2);
                testPose.orientation.x = std::sqrt(1 - u1)*std::cos(2 * PI * u2);
                testPose.orientation.y = std::sqrt(u1) * std::sin(2 * PI * u3);
                testPose.orientation.z = std::sqrt(u1) * std::cos(2 * PI * u3);

                initial_dot_product = 0.0;
                initial_dot_product = (defaultPose.orientation.w * testPose.orientation.w) +
                                       (defaultPose.orientation.x * testPose.orientation.x) +
                                       (defaultPose.orientation.y * testPose.orientation.y) +
                                       (defaultPose.orientation.z * testPose.orientation.z);
                initial_orientation_distance = 0.0;
                if (initial_dot_product < .999999){
                    initial_orientation_distance = acos((2 * pow(initial_dot_product,2)) - 1);
                }
              }      
            }    
         
            if ((x_d * 1000) < DTW_max_good_translation_err_mm && 
                (x_d * 1000) > -DTW_max_good_translation_err_mm &&
                (y_d * 1000) < DTW_max_good_translation_err_mm && 
                (y_d * 1000) > -DTW_max_good_translation_err_mm &&
                (z_d * 1000) < DTW_max_good_translation_err_mm && 
                (z_d * 1000) > -DTW_max_good_translation_err_mm &&
                abs(initial_orientation_distance) < DTW_max_good_rotation_err_rad) {
                
                valve_update.request.id = DTW_good_id;
            }
            else { valve_update.request.id = DTW_bad_id; }
          
            server->erase("valve");
			      makeValve(testPose);
            server->applyChanges();
            ros::Duration(test_delay_display_sec).sleep();
     
            if (use_valve_icp) {

              valve_request.request.valve.header.stamp = ros::Time::now();
              valve_request.request.valve.pose = testPose;
              newPose.position.x = 0;
              newPose.position.y = 0;
              newPose.position.z = 0;
              newPose.orientation.w = 1;
              newPose.orientation.x = 0;
              newPose.orientation.y = 0;
              newPose.orientation.z = 0;

              if (valve_request_client.call(valve_request)) { 
                newPose = valve_request.response.valve.pose; }
              else { ROS_ERROR("/gui/valve_interact_test.cpp: Pointcloud Request FAILED"); }

              //Calculate how well the translation was aligned
              final_position_distance = 0.0;
              final_position_distance = sqrt(pow(defaultPose.position.x - newPose.position.x, 2) +
                                       pow(defaultPose.position.y - newPose.position.y, 2) +
                                       pow(defaultPose.position.z - newPose.position.z, 2));

              //Calculate how well the orientation was aligned
              final_dot_product = 0.0;
              final_dot_product = (defaultPose.orientation.w * newPose.orientation.w) +
                                     (defaultPose.orientation.x * newPose.orientation.x) +
                                     (defaultPose.orientation.y * newPose.orientation.y) +
                                     (defaultPose.orientation.z * newPose.orientation.z);
              final_orientation_distance = 0.0;
              if (final_dot_product < .999999){
                  final_orientation_distance = acos((2 * pow(final_dot_product,2)) - 1);
              }

              valve_update.request.valve.header.stamp = ros::Time::now();
              if (use_valve_icp_answer) { valve_update.request.valve.pose = newPose; }
                else { valve_update.request.valve.pose = testPose; }
              valve_update.request.rms_err = final_position_distance;
              valve_update.request.angle_err = final_orientation_distance;

            //If we didn't run the valve align, set up for the send to robot if we're doing that
            } else {
              valve_update.request.valve.header.stamp = ros::Time::now();
              valve_update.request.valve.pose = testPose;
              valve_update.request.rms_err = initial_position_distance;
              valve_update.request.angle_err = initial_orientation_distance;
            }


            //Print Debug Information
            if (print_debug){
//              ROS_INFO("Distance (mm): %f, Orientation (deg): %f, Rating: %s", initial_position_distance * 1000, 
//                                                                    initial_orientation_distance * 57.2957795,
//                                                                    valve_update.request.id.c_str());
              ROS_INFO(",%f, %f, %f, %f, %s", initial_position_distance * 1000, 
                                         initial_orientation_distance * 57.2957795,
                                         final_position_distance * 1000,
                                         final_orientation_distance * 57.2957795,
                                         valve_update.request.id.c_str());
            }


            if (send_2_robot) {
              if (valve_update_client.call(valve_update)) { 
                  ROS_INFO("%s", valve_update.response.success_code.c_str()); 
              } else { ROS_ERROR(" **** Request from Planner ERRORRORRED"); }
            }
          
            server->erase("valve");
			      makeValve(newPose);
            server->applyChanges();
            ros::Duration(test_delay_display_sec).sleep();
          
            tests++;
          }
          break;














        case 18: //The new COMPLETE tester

          if(print_debug) {ROS_INFO("Printing Debug Information: ");
            ROS_INFO("============================================");
            
            if (defaultPose.position.x != .5 && defaultPose.position.y != 0 && defaultPose.position.z != .5){
              ROS_INFO("Default POSE has been set to: (%f, %f, %f) [%f, %f, %f, %f]", defaultPose.position.x,
                                                                                      defaultPose.position.y,
                                                                                      defaultPose.position.z,
                                                                                      defaultPose.orientation.w,
                                                                                      defaultPose.orientation.x,
                                                                                      defaultPose.orientation.y,
                                                                                      defaultPose.orientation.z);
            } else {ROS_INFO(" *** WARNING *** Default Pose is NOT Set Proceed with CAUTION ");}

            ROS_INFO("Test Iterations: %d", test_iterations);
            
            if(use_valve_icp) {ROS_INFO("Running ICP: True");}
              else{ROS_INFO("Running ICP: False");}

            if(send_2_robot) {ROS_INFO("Sending Pose 2 Robot: True");}
              else{ROS_INFO("Sending Pose 2 Robot: False");}

            if(cause_translations) {ROS_INFO("Cause translations: True");}
              else{ROS_INFO("Cause translations: False");}
            
            ROS_INFO("Max Translation (mm): %d", max_translation_mm);

            if(cause_rotations) {ROS_INFO("Cause Rotations: True");}
              else{ROS_INFO("Cause Rotations: False");}

            ROS_INFO("Max Rotation (deg): %d", max_rotation_deg);

            ROS_INFO("Dynamic Time Warping Parameters:");
            ROS_INFO("  Max \"GooD\" Translation Error (mm): %d", DTW_max_good_translation_err_mm);
            ROS_INFO("  Max \"GooD\" Rotation Error (deg): %d", DTW_max_good_rotation_err_deg);
            ROS_INFO("  \"GooD\" String ID: %s", DTW_good_id.c_str());
            ROS_INFO("  \"BaD\" String ID: %s", DTW_bad_id.c_str());
            ROS_INFO("============================================");

            

          } else { ROS_INFO("Not Printing Debug information");
                   ROS_INFO("============================================");}

          int trans_d = 0;
          int trans_i = 10;

          float angle_d = 0;
          float angle_i = 5 * 0.0174532925;

          ROS_INFO("About to Run FOR Loop");
          while(trans_d <= (max_translation_mm - trans_i)){

            while(angle_d <= (max_rotation_rad - angle_i)) {

              ROS_INFO("Setting New Test Parameters: Trans: (%d - %d), Deg: (%f - %f)", trans_d, (trans_d + trans_i), angle_d* 57.2957795, (angle_d + angle_i) * 57.2957795);
              tests = 0;

              while(tests < test_iterations){

                testPose = defaultPose;

                initial_position_distance = -1;

                while (cause_translations && (initial_position_distance * 1000) < trans_d){
//                if (cause_translations){

                    x_d = 0.0;
                    y_d = 0.0;
                    z_d = 0.0;

                    initial_position_distance = -1;
//                    max_translation_mm = trans_d + trans_i;

                    max_translation_mm = (int)sqrt(pow(trans_d + trans_i,2) / 3);

                    x_d = ((float)(std::rand() % max_translation_mm)/1000) - ((max_translation_mm / 2) / 1000);
                    y_d = ((float)(std::rand() % max_translation_mm)/1000) - ((max_translation_mm / 2) / 1000);
                    z_d = ((float)(std::rand() % max_translation_mm)/1000) - ((max_translation_mm / 2) / 1000);
                    testPose.position.x += x_d;
                    testPose.position.y += y_d;
                    testPose.position.z += z_d;

                    initial_position_distance = sqrt(pow(defaultPose.position.x - testPose.position.x, 2) +
                                             pow(defaultPose.position.y - testPose.position.y, 2) +
                                             pow(defaultPose.position.z - testPose.position.z, 2));

                }
                
                if(cause_rotations) {

                  initial_orientation_distance = -1;

                  while (initial_orientation_distance > (angle_d + angle_i) || initial_orientation_distance < angle_d) {

                    u1 = 0.0;
                    u2 = 0.0;
                    u3 = 0.0;

                    initial_orientation_distance = -1;
      
                    u1 = ((float)(std::rand() % 100)/100);
                    u2 = ((float)(std::rand() % 100)/100);
                    u3 = ((float)(std::rand() % 100)/100);
                    testPose.orientation.w = std::sqrt(1 - u1)*std::sin(2 * PI * u2);
                    testPose.orientation.x = std::sqrt(1 - u1)*std::cos(2 * PI * u2);
                    testPose.orientation.y = std::sqrt(u1) * std::sin(2 * PI * u3);
                    testPose.orientation.z = std::sqrt(u1) * std::cos(2 * PI * u3);

                    initial_dot_product = 0.0;
                    initial_dot_product = (defaultPose.orientation.w * testPose.orientation.w) +
                                           (defaultPose.orientation.x * testPose.orientation.x) +
                                           (defaultPose.orientation.y * testPose.orientation.y) +
                                           (defaultPose.orientation.z * testPose.orientation.z);
                    initial_orientation_distance = 0.0;
                    if (initial_dot_product < .999999){
                        initial_orientation_distance = acos((2 * pow(initial_dot_product,2)) - 1);
                    }
                  }      
                }    
             
                if ((x_d * 1000) < DTW_max_good_translation_err_mm && 
                    (x_d * 1000) > -DTW_max_good_translation_err_mm &&
                    (y_d * 1000) < DTW_max_good_translation_err_mm && 
                    (y_d * 1000) > -DTW_max_good_translation_err_mm &&
                    (z_d * 1000) < DTW_max_good_translation_err_mm && 
                    (z_d * 1000) > -DTW_max_good_translation_err_mm &&
                    abs(initial_orientation_distance) < DTW_max_good_rotation_err_rad) {
                    
                    valve_update.request.id = DTW_good_id;
                }
                else { valve_update.request.id = DTW_bad_id; }
              
                server->erase("valve");
			          makeValve(testPose);
                server->applyChanges();
                ros::Duration(test_delay_display_sec).sleep();
         
                if (use_valve_icp) {

                  valve_request.request.valve.header.stamp = ros::Time::now();
                  valve_request.request.valve.pose = testPose;
                  newPose.position.x = 0;
                  newPose.position.y = 0;
                  newPose.position.z = 0;
                  newPose.orientation.w = 1;
                  newPose.orientation.x = 0;
                  newPose.orientation.y = 0;
                  newPose.orientation.z = 0;

                  if (valve_request_client.call(valve_request)) { 
                    newPose = valve_request.response.valve.pose; }
                  else { ROS_ERROR("/gui/valve_interact_test.cpp: Pointcloud Request FAILED"); }

                  //Calculate how well the translation was aligned
                  final_position_distance = 0.0;
                  final_position_distance = sqrt(pow(defaultPose.position.x - newPose.position.x, 2) +
                                           pow(defaultPose.position.y - newPose.position.y, 2) +
                                           pow(defaultPose.position.z - newPose.position.z, 2));

                  //Calculate how well the orientation was aligned
                  final_dot_product = 0.0;
                  final_dot_product = (defaultPose.orientation.w * newPose.orientation.w) +
                                         (defaultPose.orientation.x * newPose.orientation.x) +
                                         (defaultPose.orientation.y * newPose.orientation.y) +
                                         (defaultPose.orientation.z * newPose.orientation.z);
                  final_orientation_distance = 0.0;
                  if (final_dot_product < .999999){
                      final_orientation_distance = acos((2 * pow(final_dot_product,2)) - 1);
                  }

                  valve_update.request.valve.header.stamp = ros::Time::now();
                  if (use_valve_icp_answer) { valve_update.request.valve.pose = newPose; }
                    else { valve_update.request.valve.pose = testPose; }
                  valve_update.request.rms_err = final_position_distance;
                  valve_update.request.angle_err = final_orientation_distance;

                //If we didn't run the valve align, set up for the send to robot if we're doing that
                } else {
                  valve_update.request.valve.header.stamp = ros::Time::now();
                  valve_update.request.valve.pose = testPose;
                  valve_update.request.rms_err = initial_position_distance;
                  valve_update.request.angle_err = initial_orientation_distance;
                }


                //Print Debug Information
                if (print_debug){
    //              ROS_INFO("Distance (mm): %f, Orientation (deg): %f, Rating: %s", initial_position_distance * 1000, 
    //                                                                    initial_orientation_distance * 57.2957795,
    //                                                                    valve_update.request.id.c_str());
                  ROS_INFO(",%f, %f, %f, %f, %s", initial_position_distance * 1000, 
                                             initial_orientation_distance * 57.2957795,
                                             final_position_distance * 1000,
                                             final_orientation_distance * 57.2957795,
                                             valve_update.request.id.c_str());
                }


                if (send_2_robot) {
                  if (valve_update_client.call(valve_update)) { 
                      ROS_INFO("%s", valve_update.response.success_code.c_str()); 
                  } else { ROS_ERROR(" **** Request from Planner ERRORRORRED"); }
                }
              
                server->erase("valve");
			          makeValve(newPose);
                server->applyChanges();
                ros::Duration(test_delay_display_sec).sleep();
              
                tests++;
              } //End While Loop
            angle_d = angle_d + angle_i;
            } //End Angle For Loop
          angle_d = 0;
          max_translation_mm = 300;
          trans_d = trans_d + trans_i;
          } //End Translation For Loop
          break;














        } //END switch(feedback->menu_entry_id){

        break;
	} //END switch (feedback->event_type){
}



////////////////////////////////////////////////////////////////////////////////////



void makeValve(geometry_msgs::Pose newPose){

// ********* Initialize ********* //

  resource_retriever::Retriever r;

  Marker marker;
  marker.type = Marker::MESH_RESOURCE;
	marker.mesh_resource = "package://wpi_drc_sim/meshes/valve_models/logitech_driving_force_pro_wheel.dae";
  marker.scale.x = marker_size;
  marker.scale.y = marker_size;
  marker.scale.z = marker_size;
  marker.color.r = 1.0;
  marker.color.g = 0;
  marker.color.b = 0;
  marker.color.a = 1.0;

  InteractiveMarker int_marker;
  int_marker.header.frame_id = "/torso_lift_link";
  int_marker.name = "valve";
  int_marker.description = "Align the Valve!";
  int_marker.pose.position.x = newPose.position.x;
  int_marker.pose.position.y = newPose.position.y;
  int_marker.pose.position.z = newPose.position.z;
  int_marker.pose.orientation.x = newPose.orientation.x;
  int_marker.pose.orientation.y = newPose.orientation.y;
  int_marker.pose.orientation.z = newPose.orientation.z;
  int_marker.pose.orientation.w = newPose.orientation.w;



// ********* The Model to Control ********* //  
  InteractiveMarkerControl control_box;
  control_box.always_visible = true;
  control_box.markers.push_back( marker );
  int_marker.controls.push_back( control_box );
  int_marker.controls.back();



// ********* The Menu Controller ********* //  
  InteractiveMarkerControl control_menu;
  control_menu.interaction_mode = InteractiveMarkerControl::MENU;
  int_marker.controls.push_back(control_menu);
  


// ********* The Pose Controls ********* // 
  InteractiveMarkerControl control_pose;
  control_pose.orientation_mode = InteractiveMarkerControl::FIXED;

	//X-axis rotation and movement
  control_pose.orientation.w = 1;
  control_pose.orientation.x = 1;
  control_pose.orientation.y = 0;
  control_pose.orientation.z = 0;
  control_pose.name = "rotate_x";
  control_pose.interaction_mode = InteractiveMarkerControl::ROTATE_AXIS;
  int_marker.controls.push_back(control_pose);

  control_pose.name = "move_x";
  control_pose.interaction_mode = InteractiveMarkerControl::MOVE_AXIS;
  int_marker.controls.push_back(control_pose);

	//Y-axis rotation and movement
  control_pose.orientation.w = 1;
  control_pose.orientation.x = 0;
  control_pose.orientation.y = 1;
  control_pose.orientation.z = 0;
  control_pose.name = "rotate_y";
  control_pose.interaction_mode = InteractiveMarkerControl::ROTATE_AXIS;
  int_marker.controls.push_back(control_pose);

  control_pose.name = "move_y";
  control_pose.interaction_mode = InteractiveMarkerControl::MOVE_AXIS;
  int_marker.controls.push_back(control_pose);

	//Z-axis rotation and movement
  control_pose.orientation.w = 1;
  control_pose.orientation.x = 0;
  control_pose.orientation.y = 0;
  control_pose.orientation.z = 1;
  control_pose.name = "rotate_z";
  control_pose.interaction_mode = InteractiveMarkerControl::ROTATE_AXIS;
  int_marker.controls.push_back(control_pose);

  control_pose.name = "move_z";
  control_pose.interaction_mode = InteractiveMarkerControl::MOVE_AXIS;
  int_marker.controls.push_back(control_pose);



// ********* Update The Server ********* //  
	//"Publish" the marker to the server
  server->insert(int_marker, &processFeedback);
  menu_handler.apply( *server, int_marker.name );

}


// %Tag(main)%
int main(int argc, char** argv)
{
  ros::init(argc, argv, "valve_interact");
  ros::NodeHandle n;
    
  //Set Important ROS Parameters
  n.setParam("/gui/valve_interact/cause_translations", true);
  n.setParam("/gui/valve_interact/cause_rotations", true);
  n.setParam("/gui/valve_interact/max_rotation_deg", 25);
  n.setParam("/gui/valve_interact/max_translation_mm", 300);
  n.setParam("/gui/valve_interact/test_iterations", 10);
  n.setParam("/gui/valve_interact/DTW_max_good_translation_err_mm", 10);
  n.setParam("/gui/valve_interact/DTW_max_good_rotational_err_deg", 10);
  n.setParam("/gui/valve_interact/DTW_good_id", "KG-EX");
  n.setParam("/gui/valve_interact/DTW_bad_id", "KB-EX");
  n.setParam("/gui/valve_interact/use_valve_icp", true);
  n.setParam("/gui/valve_interact/use_valve_icp_answer", true);
  n.setParam("/gui/valve_interact/send_2_robot", false);
  n.setParam("/gui/valve_interact/print_debug", true);
  n.setParam("/gui/valve_interact/test_display_delay_sec", 0);
  
  
  server = new interactive_markers::InteractiveMarkerServer("valve_interact_server","",false);
  ros::Duration(.1).sleep();
  
  //Client Created Here
  valve_request_client = n.serviceClient<gui::updateValvePos>("request_valve_pose");
  valve_update_client = n.serviceClient<gui::updateValvePos>("update_valve_pose");






  menu_handler.insert( "Align 2 Cloud", &processFeedback );
  menu_handler.insert( "Send 2 Robot", &processFeedback );
  interactive_markers::MenuHandler::EntryHandle sub_menu_handle = menu_handler.insert( "Re-Size" );
  menu_handler.insert( sub_menu_handle, "50%", &processFeedback );
  menu_handler.insert( sub_menu_handle, "60%", &processFeedback );
  menu_handler.insert( sub_menu_handle, "70%", &processFeedback );
  menu_handler.insert( sub_menu_handle, "80%", &processFeedback );  
  menu_handler.insert( sub_menu_handle, "90%", &processFeedback );
  menu_handler.insert( sub_menu_handle, "* RESET SIZE *", &processFeedback );
  menu_handler.insert( sub_menu_handle, "110%", &processFeedback );
  menu_handler.insert( sub_menu_handle, "120%", &processFeedback );
  menu_handler.insert( sub_menu_handle, "130%", &processFeedback );
  menu_handler.insert( sub_menu_handle, "140%", &processFeedback );  
  menu_handler.insert( sub_menu_handle, "150%", &processFeedback );
  menu_handler.insert( "MAKE New Session Default", &processFeedbackTESTING );
  menu_handler.insert( "MOVE to Session Default", &processFeedbackTESTING );
  menu_handler.insert( "RUN Tests", &processFeedbackTESTING );
  menu_handler.insert( "RUN Incremental Tests", &processFeedbackTESTING );
//  menu_handler.insert( "Send2Robot - (3cm OFF, 100x)", &processFeedbackTESTING);

  defaultPose.position.x = .5;
  defaultPose.position.y = 0;
  defaultPose.position.z = .5;
  defaultPose.orientation.x = 0;
  defaultPose.orientation.y = 0;
  defaultPose.orientation.z = 1;
  defaultPose.orientation.w = 0;

  //XXX Stuff for testing
  std::srand(ros::Time::now().toSec());  
  

	makeValve(defaultPose);
  server->applyChanges();
  ros::spin();
}
// %EndTag(main)%
