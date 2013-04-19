#include <ros/ros.h>
#include <string>
#include <sensor_msgs/PointCloud2.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>

// PCL specific includes
#include "pcl_ros/transforms.h"
#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

#include <pcl/io/io.h>
#include "pcl_ros/io/concatenate_data.h"

//Create a publisher
ros::Publisher pub;
pcl::PointCloud<pcl::PointXYZ> world_cloud;
sensor_msgs::PointCloud2 world_cloud_ros;
int once = 1;
int count = 0;

//Create a TransformListener
tf::TransformListener* myListener = NULL;


/**
 * Notes:
 * Might be able to make use of pcl::concatenatePointCloud
 * http://docs.pointclouds.org/trunk/group__common.html
 *
 * RadiusOutlierRemoval
 * http://docs.pointclouds.org/1.0.0/namespacepcl.html
 *
 * StatisticalOutlierRemoval
 * http://docs.pointclouds.org/1.0.0/namespacepcl.html
 *
 *
 **/

void cloud_cb (sensor_msgs::PointCloud2Ptr input_raw) {

/**
  world_cloud_ros.header = input_raw->header;

  if (once % 5 == 0) {

    ROS_INFO("Combining Cloud");
  
    sensor_msgs::PointCloud2 world_temp;

    //Combine the new point cloud with the world cloud
    pcl::concatenatePointCloud (*input_raw, world_cloud_ros,  world_temp);
    world_cloud_ros = world_temp;
  
  }
  pub.publish(world_cloud_ros); 
  once++;
**/


  pcl::VoxelGrid<sensor_msgs::PointCloud2> voxel_filter;
  voxel_filter.setLeafSize(.01, .01, .01);
  voxel_filter.setInputCloud(input_raw);
  voxel_filter.filter(*input_raw);

  //Convert the sensor_msgs into an actual point cloud
  pcl::PointCloud<pcl::PointXYZ> input_pcl;  
  pcl::fromROSMsg(*input_raw, input_pcl);

  //Transform the input into the /odom_combined frame
  std::string target_frame;
  target_frame = "/odom_combined";
  
  pcl_ros::transformPointCloud(target_frame, input_pcl, input_pcl, *myListener);

  //Add the cloud to the world cloud
  world_cloud += input_pcl;

  //Convert the world back to a sensor_msgs
  sensor_msgs::PointCloud2::Ptr world (new sensor_msgs::PointCloud2 ());
  pcl::toROSMsg(world_cloud, *world);
//  world->header = input_raw->header;
  
  //Change the world to be in the /odom_combined frame
  world->header = input_raw->header;
  world->header.frame_id = target_frame;

  //Filter the World

  if (count % 20 == 0) {

    ROS_INFO("Filtering the World!");

    voxel_filter.setLeafSize(.01, .01, .01);
    voxel_filter.setInputCloud(world);
    voxel_filter.filter(*world);
  
  }
  
  //Turn it back into the cloud we're saving
  world_cloud.clear();
  pcl::fromROSMsg(*world, world_cloud);
  
  pub.publish(*world);
  
//  ROS_INFO("World_Cloud Size: %d", world_cloud.size());

  count++;


/**
  //Convert the sensor_msgs into an actual point cloud
  pcl::PointCloud<pcl::PointXYZ> input_pcl;
  pcl::fromROSMsg(*input_raw, input_pcl);

  //Transform the input into the /odom_combined frame
  

  //Add the cloud to the world cloud
  world_cloud += input_pcl;

  //Convert the world back to a sensor_msgs
  sensor_msgs::PointCloud2::Ptr world (new sensor_msgs::PointCloud2 ());
  pcl::toROSMsg(world_cloud, *world);
  world->header = input_raw->header;
  
  //Change the world to be in the /odom_combined frame

  //Filter the World
  pcl::VoxelGrid<sensor_msgs::PointCloud2> voxel_filter;
  voxel_filter.setLeafSize(.005, .005, .005);
  voxel_filter.setInputCloud(world);
  voxel_filter.filter(*world);
  
  //Turn it back into the cloud we're saving
  world_cloud.clear();
  pcl::fromROSMsg(*world, world_cloud);
  
  pub.publish(*world);
  
  ROS_INFO("World_Cloud Size: %d", world_cloud.size());
**/

}

int main (int argc, char** argv) {

  // Initialize ROS
  ros::init (argc, argv, "pointcloud_server");
  ros::NodeHandle nh;

  //Publisher
  pub = nh.advertise<sensor_msgs::PointCloud2>("/camera/depth/world", 100);
  
  //Create a TransformListener
  myListener = new(tf::TransformListener);

  //Start looking for the transform between the valve and the camera frame
  bool found = false;
  while (found == false){
    found = myListener->waitForTransform("/camera_depth_optical_frame", "/odom_combined", ros::Time(), ros::Duration(1));
  }
 
  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub = nh.subscribe ("/camera/depth/points", 100, cloud_cb);
 
  ROS_INFO("Ready to Proceed Captain");


  // Spin
  ros::spin ();
}
