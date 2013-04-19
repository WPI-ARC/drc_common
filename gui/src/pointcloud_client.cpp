#include "ros/ros.h"
#include "gui/pointcloud.h"

ros::ServiceClient client;

bool pointcloud_update(gui::pointcloud::Request  &req,
           	            gui::pointcloud::Response &res ) {
  
  //If it doesn't want to cached one
  gui::pointcloud srv;
  srv.request.voxel = req.voxel;
  srv.request.x = req.x;
  srv.request.y = req.y;
  srv.request.z = req.z;
  
  if(client.call(srv)){ 
    res.pointcloud = srv.response.pointcloud;
    return true;
  }
	else { 
	  ROS_ERROR("/gui/pointcloud_client.cpp: Pointcloud Update FAILED");
	  return false;
	}

}


int main(int argc, char **argv) {
	ros::init(argc, argv, "pointcloud_client");

  //Setup the ROS node
	ros::NodeHandle nh;

  //Create a ROS Service Server
  ros::ServiceServer server = nh.advertiseService("/gui/pointcloud_update", pointcloud_update);

  //Setup the client that will be sending commands back to the robot
	client = nh.serviceClient<gui::pointcloud>("/gui/pointcloud_request");
	
	
	
  //Spin while we wait for callbacks
  ros::spin ();

return 0;

}
