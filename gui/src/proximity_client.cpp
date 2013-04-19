#include <cstdlib>
#include <vector>

#include "ros/ros.h"
#include <std_msgs/Float32.h>
#include <nav_msgs/Odometry.h>
#include <pcl/point_types.h>

#include <sensor_msgs/PointCloud2.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>

// PCL specific includes
#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/io/pcd_io.h>
#include <pcl/registration/icp.h>

#include "gui/proximity_srv.h"
#include "gui/proximity_msg.h"


#define PROXIMITY_SENSORS 4

#define PROXIMITY_MIN   0.1
#define PROXIMITY_MAX   2.0
#define PROXIMITY_DELTA 0.1
#define PROXIMITY_POINTS ((PROXIMITY_MAX - PROXIMITY_MIN) / PROXIMITY_DELTA)

ros::Publisher pub_proximity;
sensor_msgs::PointCloud2 recent_raw_cloud;
pcl::PointCloud<pcl::PointXYZ> recent_cloud; //A Filtered Version of the most recent cloud

bool have_cloud = false;

/**
 * Odometry from Turtlebot is in the /odom frame
 *
 *
 */
void proximity_cb (nav_msgs::Odometry position){

  if (have_cloud) {

      std::vector<float> distances(PROXIMITY_SENSORS);

      //Determine where we are in the world from position
      geometry_msgs::Pose myPose;
      myPose = position.pose.pose; //The pose is nested within a covariance

      //Determine the twist (Theta or Psi) of the robot
      float theta = 0;

      //Convert the point cloud into the robot's frame (DO THIS IN CLOUD_CB?)

      //For each sensor, determine what is closest to it
      for (int i = 0; i < PROXIMITY_SENSORS; i++){

        //Look through from min to max to try and find a cloud
        for (int j = 0; j < PROXIMITY_POINTS; j++){

          

        }

        //Add a given amount to theta for the next run

      }


      //Determine range from objects along that line

      //Format the Proximity Message

      //Publish

  }

}

void cloud_cb (const sensor_msgs::PointCloud2ConstPtr& input) {

  //Copy over the header information
  recent_raw_cloud.header = input->header;

  //Add a Voxel filter to the cloud before creating the points
	sensor_msgs::PointCloud2 input_voxel;  
	pcl::VoxelGrid<sensor_msgs::PointCloud2> raw_voxel_cloud;
	raw_voxel_cloud.setInputCloud(input);
	raw_voxel_cloud.setLeafSize(.01, .01, .01);
	raw_voxel_cloud.filter(input_voxel);

	//These functions will convert from the sensor_msg to the cloud of real points
	pcl::fromROSMsg(input_voxel, recent_cloud);

  have_cloud = true;

}

int main(int argc, char **argv) {
	ros::init(argc, argv, "proximity_client");

  //Setup everything for the publishes	
	ros::NodeHandle nh;
	ros::Publisher pub_user_command;

  //Advertise the two publishers, one for the commands and one for the gui
	pub_proximity = nh.advertise<gui::proximity_msg>("/gui/proximity_client/proximity", 100);
	pub_user_command = nh.advertise<std_msgs::Float32>("/gui/proximity_client/user_command", 100);

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub_cloud = nh.subscribe ("/camera/depth/points", 100, cloud_cb);

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub_odom = nh.subscribe ("/odom", 100, proximity_cb);

  //Setup the service that will be getting the data
	ros::ServiceClient client = nh.serviceClient<gui::proximity_srv>("proximity_srv");
	gui::proximity_srv srv;

  ros::spin();
  
/** 	
	ros::Rate r(1);//Hz

	while(ros::ok()){

    //We need to request something so this is just random data
		srv.request.user_request = 1;

    //Try to call the server
		if(client.call(srv)){
			
      //Increment how many times we've gotten proximity data
      calls++;

			//Announce that the Call to the Service Worked
			ROS_INFO("PROXIMITY_CLIENT: Proximity Data Received: %d", srv.response.proximity);

			//Create and publish a new proximity message to rviz
			gui_base_pkg::proximity_msg myProx;
			myProx.header.frame_id = "/odom_combined";
			myProx.header.stamp = ros::Time::now();
			myProx.bars = bars;
			myProx.data = 1;
			pub_gui.publish(myProx);

      bars++;
 
      if (bars > 10) {bars = 1;}

      //Every 30 calls publish a command to the user
      if(calls == 30) {

        ROS_INFO("PROXIMITY_CLIENT: Generating a User_Command");

			  //Create an publish a new message to user_command_client
			  std_msgs::Float32 myVar;
			  myVar.data= srv.response.proximity + 2;
			  pub_user_command.publish(myVar);

        //Reset the number of calls
        calls = 0;

      }


		}
		else {
			ROS_INFO("PROXIMITY_CLIENT: Request for Proximity Data FAILED");
		}

		r.sleep();

	}
 **/
  return 0;

}
