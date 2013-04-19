#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/LaserScan.h>

//Create a publisher
ros::Publisher pub;

void state_1_cb (const sensor_msgs::LaserScan input) {
	std_msgs::Float32 myVar;
	myVar.data=1.0;
	pub.publish(myVar);

}

void state_2_cb (const std_msgs::Float32 input) { }
void state_3_cb (const std_msgs::Float32 input) { }
void state_4_cb (const std_msgs::Float32 input) { }
void state_5_cb (const std_msgs::Float32 input) { }
void state_6_cb (const std_msgs::Float32 input) { }
void state_7_cb (const std_msgs::Float32 input) { }
void state_8_cb (const std_msgs::Float32 input) { }


int main (int argc, char** argv) {

  // Initialize ROS
  ros::init (argc, argv, "robot_state");
  ros::NodeHandle nh;
  ros::Subscriber sub_1;
  ros::Subscriber sub_2;
  ros::Subscriber sub_3;
  ros::Subscriber sub_4;
  ros::Subscriber sub_5;
  ros::Subscriber sub_6;
  ros::Subscriber sub_7;
  ros::Subscriber sub_8;
  

  //Create subscribers to messages
  if (ros::param::has("robot_state_topic_1")) {
    std::string robot_state_topic_1;
    ros::param::get("robot_state_topic_1", robot_state_topic_1);
    sub_1 = nh.subscribe ("/tilt_scan", 100, state_1_cb);
  }
  
  if (ros::param::has("robot_state_topic_2")) {
    std::string robot_state_topic_2;
    ros::param::get("robot_state_topic_2", robot_state_topic_2);
    sub_2 = nh.subscribe ((std::string)robot_state_topic_2, 100, state_2_cb);
  }
  
  if (ros::param::has("robot_state_topic_3")) {
    std::string robot_state_topic_3;
    ros::param::get("robot_state_topic_3", robot_state_topic_3);
    sub_3 = nh.subscribe ((std::string)robot_state_topic_3, 100, state_3_cb);
  }
  
  if (ros::param::has("robot_state_topic_4")) {
    std::string robot_state_topic_4;
    ros::param::get("robot_state_topic_4", robot_state_topic_4);
    sub_4 = nh.subscribe ((std::string)robot_state_topic_4, 100, state_4_cb);
  }

  if (ros::param::has("robot_state_topic_5")) {
    std::string robot_state_topic_5;
    ros::param::get("robot_state_topic_5", robot_state_topic_5);
    sub_5 = nh.subscribe ((std::string)robot_state_topic_5, 100, state_5_cb);
  }
  
  if (ros::param::has("robot_state_topic_6")) {
    std::string robot_state_topic_6;
    ros::param::get("robot_state_topic_6", robot_state_topic_6);
    sub_6 = nh.subscribe ((std::string)robot_state_topic_6, 100, state_6_cb);
  }
  
  if (ros::param::has("robot_state_topic_7")) {
    std::string robot_state_topic_7;
    ros::param::get("robot_state_topic_7", robot_state_topic_7);
    sub_7 = nh.subscribe ((std::string)robot_state_topic_7, 100, state_7_cb);
  }
  
  if (ros::param::has("robot_state_topic_8")) {
    std::string robot_state_topic_8;
    ros::param::get("robot_state_topic_8", robot_state_topic_8);
    sub_8 = nh.subscribe ((std::string)robot_state_topic_8, 100, state_8_cb);
  }

	//Create and advertise a ROS publisher
	pub = nh.advertise<std_msgs::Float32>("/sensor_pkg/robot_state", 100);

  // Spin
  ros::spin ();

return 0;
}
