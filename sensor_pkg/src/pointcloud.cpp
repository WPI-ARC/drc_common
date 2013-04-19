#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

//Create a publisher
ros::Publisher pub;

void pointcloud_cb (sensor_msgs::PointCloud2 input){

  pub.publish(input);

}

int main (int argc, char** argv) {

  // Initialize ROS and the NodeHandle
  ros::init (argc, argv, "pointcloud");
  
  ros::NodeHandle nh;
  
  std::string pointcloud_topic;
  
  ros::param::get("pointcloud_topic", pointcloud_topic);

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub = nh.subscribe ((std::string)pointcloud_topic, 100, pointcloud_cb);

	//Create and advertise a ROS publisher
  pub = nh.advertise<sensor_msgs::PointCloud2>("/sensor_pkg/pointcloud", 100); 

  // Spin
  ros::spin ();

  return 0;
}
