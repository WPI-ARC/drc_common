#include <ros/ros.h>
#include "gui/user_command_srv.h"

/**
 * This function gets called whenever the user wants to send back a command to
 * the robot.  It needs to be updated to let the perception and arm_test
 * packages know that it got a command 
 */
bool user_command_request(gui::user_command_srv::Request  &req,
           	          gui::user_command_srv::Response &res ) {

  //Let everyone know that we got a command
  ROS_INFO("USER_COMMAND_SERVER: Command Received, Calling ____");

  //Respond with a 1 that we executed the command 
  res.command_executed = 1;

  return true;
}

int main (int argc, char** argv) {

  // Initialize ROS
  ros::init (argc, argv, "user_command_server");
  ros::NodeHandle nh;

  //Create a ROS Service Server
  ros::ServiceServer server = nh.advertiseService("user_command_srv", user_command_request);

  // Spin
  ros::spin ();

return 0;
}
