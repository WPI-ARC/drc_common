#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/LaserScan.h>

//Create a publisher
ros::Publisher pub;

void tilt_scan_cb (const sensor_msgs::LaserScan input) {
	std_msgs::Float32 myVar;
	myVar.data=1.0;
	pub.publish(myVar);

}

void base_scan_cb (const sensor_msgs::LaserScan input) {
	std_msgs::Float32 myVar;
	myVar.data=2.0;
	pub.publish(myVar);


}

int main (int argc, char** argv) {

  // Initialize ROS
  ros::init (argc, argv, "collision_map");
  ros::NodeHandle nh;

	//Create and advertise a ROS publisher
	pub = nh.advertise<std_msgs::Float32>("/sensor_pkg/collision_map", 100);

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub_tilt = nh.subscribe ("/scan", 100, tilt_scan_cb);
  //ros::Subscriber sub_base = nh.subscribe ("/base_scan", 100, base_scan_cb);

  // Spin
  ros::spin ();

return 0;
}
