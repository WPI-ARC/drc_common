#include "ros/ros.h"
#include <std_msgs/Float32.h>
#include "gui/user_command_srv.h"
#include <cstdlib>

ros::ServiceClient client;
gui::user_command_srv srv;

/**
 * This function is called whenever the proximity package generates a command
 * 
 * Add anything that would be user command related here
 */
void proximity_command_cb(const std_msgs::Float32 input) {

  //The request is the same as the input data
	srv.request.a = input.data;

  //Try and make the call down to the robot
	if(client.call(srv)){
		ROS_INFO("USER_COMMAND_CLIENT: Command Received: %d", srv.response.command_executed);
	}
	else {
		ROS_INFO("USER_COMMAND_CLIENT: Request for Command FAILED");
	}

}

int main(int argc, char **argv) {
	ros::init(argc, argv, "user_command_client");

  //Setup the ROS node
	ros::NodeHandle nh;

  //Setup the client that will be sending commands back to the robot
	client = nh.serviceClient<gui::user_command_srv>("user_command_srv");

  //Setup the subscriber that will be listening for commands from the proximity server
	ros::Subscriber sub_collision_map = nh.subscribe ("/gui/proximity_client/user_command", 100, proximity_command_cb);
	
  //Spin while we wait for callbacks
  ros::spin ();

return 0;

}
