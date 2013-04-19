#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

#include "gui/pointcloud.h"

sensor_msgs::PointCloud2 cloud;

bool pointcloud_request(gui::pointcloud::Request  &req,
           	            gui::pointcloud::Response &res ) {

  //If necessary do things here like voxel

  //Respond with the most recent pointcloud
  res.pointcloud = cloud;

  return true;
}

void pointcloud_cb (sensor_msgs::PointCloud2 input){

  cloud = input;

}

int main (int argc, char** argv) {

  // Initialize ROS
  ros::init (argc, argv, "pointcloud_server");
  ros::NodeHandle nh;

  //Create Subscriber
  ros::Subscriber sub = nh.subscribe("/sensor_pkg/pointcloud", 1, pointcloud_cb);

  //Create a ROS Service Server
  ros::ServiceServer server = nh.advertiseService("/gui/pointcloud_request", pointcloud_request);

  // Spin
  ros::spin ();

return 0;
}
