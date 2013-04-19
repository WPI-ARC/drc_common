#include <iostream>
#include <ros/ros.h>
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
#include <pcl/common/transforms.h>

//User Made Packages / Messages
#include "gui/pointcloud.h"
#include "gui/updateValvePos.h"

#include <math.h>

#define PI 3.14159265

ros::ServiceClient pointcloud_update_client;

//Create a point cloud to hold the most recent cloud aquired
sensor_msgs::PointCloud2 recent_raw_cloud;
pcl::PointCloud<pcl::PointXYZ> recent_cloud; //A Filtered Version of the most recent cloud

//Create a TransformListener
tf::TransformListener* myListener = NULL;



bool valve_request(gui::updateValvePos::Request  &req,
           	       gui::updateValvePos::Response &res ) {

	//Create Point Cloud Objects Needed for this function (Cleanup later?)
  pcl::PointCloud<pcl::PointXYZ> input_cloud;
  pcl::PointCloud<pcl::PointXYZ> valve_cloud;
  pcl::PointCloud<pcl::PointXYZ> valve_cloud_input;
  pcl::PointCloud<pcl::PointXYZ> valve_cloud_aligned;
  pcl::PointCloud<pcl::PointXYZ>::Ptr icp_target (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr icp_input (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ> Final; //Used for ICP Alignment
  sensor_msgs::PointCloud2 output_aligned; //Output back to ROS
  sensor_msgs::PointCloud2 output_valve; //Output back to ROS

  //Create a new msg that will hold the pose of the valve in the cloud's frame
  geometry_msgs::PoseStamped v_cloud;
  
  //Wait for the transform to become available
  std::string pointcloud_frame;
  std::string target_frame;
  ros::param::get("pointcloud_frame", pointcloud_frame);
  ros::param::get("target_frame", target_frame);
  myListener->waitForTransform((std::string)pointcloud_frame, (std::string)target_frame, req.valve.header.stamp, ros::Duration(1));

  //Transform the valve into the cloud frame

  myListener->transformPose((std::string)pointcloud_frame,
                            req.valve.header.stamp,
                            req.valve, 
                            (std::string)target_frame,
                            v_cloud);

//  myListener->transformPose((std::string)pointcloud_frame, req.valve, v_cloud);

  //Initialize the cloud that will hold the points in the bounding box of the valve
  input_cloud.width = 0;
  input_cloud.height = 0;
  input_cloud.is_dense = false;
  
  valve_cloud.width = 0;
  valve_cloud.height = 0;
  valve_cloud.is_dense = false;





  //Request a Cloud from the Pointcloud Client
  sensor_msgs::PointCloud2 myCloud;
  gui::pointcloud pointcloud_update;
  pointcloud_update.request.voxel = true;
  pointcloud_update.request.x = .01;
  pointcloud_update.request.y = .01;
  pointcloud_update.request.z = .01;
  
  if (pointcloud_update_client.call(pointcloud_update)) { 
    myCloud = pointcloud_update.response.pointcloud;
  }
  else { ROS_ERROR("/gui/valve_icp_test.cpp: Pointcloud Update FAILED"); }
  //Add a Voxel filter to the cloud before creating the points
	sensor_msgs::PointCloud2 input_voxel;
	const sensor_msgs::PointCloud2::Ptr input_cloud_ptr;
	
//	ROS_INFO("About To Fail");
	
//	*input_cloud_ptr = myCloud;
	
//	ROS_INFO("Never Prints This");
	
//	pcl::VoxelGrid<sensor_msgs::PointCloud2> voxel_filter;
//	voxel_filter.setInputCloud(input_cloud_ptr);
//	voxel_filter.setLeafSize(.01, .01, .01);
//	voxel_filter.filter(input_voxel);

  input_voxel = myCloud;

	//These functions will convert from the sensor_msg to the cloud of real points
	pcl::fromROSMsg(input_voxel, recent_cloud);



  

  //Add points to the cloud that are in the bounding box of the valve
  for (unsigned int i = 0; i < recent_cloud.size(); i++){

    if ((recent_cloud.points[i].x > v_cloud.pose.position.x - .25    &&
         recent_cloud.points[i].x < v_cloud.pose.position.x + .25 )  &&
        (recent_cloud.points[i].y > v_cloud.pose.position.y - .25    &&
         recent_cloud.points[i].y < v_cloud.pose.position.y + .25 )  &&
        (recent_cloud.points[i].z > v_cloud.pose.position.z - .25    &&
         recent_cloud.points[i].z < v_cloud.pose.position.z + .25 )) {

      pcl::PointXYZ myPoint;
      myPoint.x = recent_cloud.points[i].x;
      myPoint.y = recent_cloud.points[i].y;
      myPoint.z = recent_cloud.points[i].z;

      input_cloud.points.push_back(myPoint);
      input_cloud.width++;
      input_cloud.height = 1;
    }

  }


  //Create the two clouds that will be used by the ICP, in the future this will
  //Changed so that icp_target is created above and icp_input is created from
  //The location of the valve and a radius around the valve.
  icp_target->width = input_cloud.width;
  icp_target->height = input_cloud.height;
  icp_target->is_dense = input_cloud.is_dense;
  icp_target->points.resize(icp_target->width * icp_target->height);




  //Create the original Valve Cloud
  int points_to_create = 360;
  float delta = (2 * PI) / points_to_create;
  float radius = req.radius;
  int rows = 2;
  
  for (unsigned int i = 0; i < points_to_create; i++){
    
    
    //TODO Check that this works
    for (int j = 0; j < rows; j++) {
    
      pcl::PointXYZ myPoint;

      myPoint.x = (radius + ((float)j / 100)) * cos(i * delta);
      myPoint.y = (radius + ((float)j / 100)) * sin(i * delta);
      myPoint.z = 0;

      valve_cloud.points.push_back(myPoint);
      valve_cloud.width++;
      valve_cloud.height = 1;

    }
  
  }

  tf::Quaternion valveOrientation;
  tf::quaternionMsgToTF(v_cloud.pose.orientation, valveOrientation);

  //This is so fucking assinine
  tf::Matrix3x3 valveRotationMatrix(valveOrientation);
  
//  ROS_INFO(" "); 
//  ROS_INFO("Raw Matrix From Valve");                         
//  for (int i = 0; i < 3; i++){ 
//    ROS_INFO("[%f, %f, %f]",  valveRotationMatrix[i][0], valveRotationMatrix[i][1], valveRotationMatrix[i][2]); 
//  }
    
  tfScalar yaw_1 = 0;
  tfScalar pitch_1 = 0;
  tfScalar roll_1 = 0;  
    
  valveRotationMatrix.getEulerYPR(yaw_1, pitch_1, roll_1);
//  ROS_INFO("Yaw: %f, Pitch: %f, Roll: %f", yaw_1, pitch_1, roll_1);
  
  tf::Matrix3x3 correction(0, 0, 1,
                           0, 1, 0,
                          -1, 0, 0);

  valveRotationMatrix*=correction;
  
  Eigen::Matrix4f valveTransformMatrix;

  valveTransformMatrix(0,0) = valveRotationMatrix[0][0];
  valveTransformMatrix(0,1) = valveRotationMatrix[0][1];
  valveTransformMatrix(0,2) = valveRotationMatrix[0][2];
  valveTransformMatrix(0,3) = v_cloud.pose.position.x;

  valveTransformMatrix(1,0) = valveRotationMatrix[1][0];
  valveTransformMatrix(1,1) = valveRotationMatrix[1][1];
  valveTransformMatrix(1,2) = valveRotationMatrix[1][2];
  valveTransformMatrix(1,3) = v_cloud.pose.position.y;

  valveTransformMatrix(2,0) = valveRotationMatrix[2][0];
  valveTransformMatrix(2,1) = valveRotationMatrix[2][1];
  valveTransformMatrix(2,2) = valveRotationMatrix[2][2];
  valveTransformMatrix(2,3) = v_cloud.pose.position.z;

  valveTransformMatrix(3,0) = 0;
  valveTransformMatrix(3,1) = 0;
  valveTransformMatrix(3,2) = 0;
  valveTransformMatrix(3,3) = 1;
 
  pcl::transformPointCloud(valve_cloud, valve_cloud_input, valveTransformMatrix);



  //Create the icp_input cloud
  icp_input->width = points_to_create * rows;
  icp_input->height = 1;
  icp_input->is_dense = input_cloud.is_dense;
  icp_input->points.resize(icp_input->width * icp_input->height);

  for (int i = 0; i < valve_cloud_input.size(); i++) {

    icp_input->points[i].x = valve_cloud_input.points[i].x;
    icp_input->points[i].y = valve_cloud_input.points[i].y;
    icp_input->points[i].z = valve_cloud_input.points[i].z;

  }



  //Copy the points into the new cloud and translate the valve by a little bit
  //So that we can see how well the algorithm performs
  for (unsigned int i = 0; i < input_cloud.size(); i++){
    icp_target->points[i].x = input_cloud.points[i].x;
    icp_target->points[i].y = input_cloud.points[i].y;
    icp_target->points[i].z = input_cloud.points[i].z;

  }



  //Create a ICP object, set parameters, give it input and target
  pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
  icp.setMaxCorrespondenceDistance (0.25f);
  icp.setMaximumIterations (600);
  icp.setInputCloud(icp_input);
  icp.setInputTarget(icp_target);

  //Align the two clouds
  icp.align(Final);

  //Do something to copy over output cloud here
  pcl::transformPointCloud(valve_cloud_input, valve_cloud_aligned, icp.getFinalTransformation());





  //EVERYTHING ABOVE HERE WORKS PERFECTLY





  //Save the matrix from the transformation 
  Eigen::Matrix4f myTransform = icp.getFinalTransformation();
  Eigen::Matrix4f finalPosition = myTransform*valveTransformMatrix;


//  ROS_INFO(" ");
//  ROS_INFO("Transformation Matrix");
//  for (int i = 0; i < 4; i++){
  
//    ROS_INFO("[%f, %f, %f, %f]",  myTransform(i,0), myTransform(i,1), myTransform(i,2), myTransform(i,3));

//  }
  
//  ROS_INFO(" ");
//  ROS_INFO("Final Position Matrix");
//  for (int i = 0; i < 4; i++){
  
//    ROS_INFO("[%f, %f, %f, %f]",  finalPosition(i,0), finalPosition(i,1), finalPosition(i,2), finalPosition(i,3));

//  }

  tf::Matrix3x3 myTfMatrix(myTransform(0,0), myTransform(0,1), myTransform(0,2),
                           myTransform(1,0), myTransform(1,1), myTransform(1,2),
                           myTransform(2,0), myTransform(2,1), myTransform(2,2));
                           
  //Create the update to the valve
  v_cloud.pose.position.x = finalPosition(0, 3);
  v_cloud.pose.position.y = finalPosition(1, 3); 
  v_cloud.pose.position.z = finalPosition(2, 3);
  
  
//  ROS_INFO(" ");
//  ROS_INFO("Post Correction Matrix:");
//  for (int i = 0; i < 3; i++){ 
//    ROS_INFO("[%f, %f, %f]",  myTfMatrix[i][0], myTfMatrix[i][1], myTfMatrix[i][2]); }
  
  //Turn the rotation matrix into a Quaternion
  tfScalar yaw = 0;
  tfScalar pitch = 0;
  tfScalar roll = 0;

  myTfMatrix.getEulerYPR(yaw, pitch, roll);
//  ROS_INFO("Yaw: %f, Pitch: %f, Roll: %f", yaw, roll, pitch);

  //Multiply the Quaternions to get my new Orientation
//  tf::Quaternion myTfQuaternion(-1 * roll, yaw, -1 * pitch);
//  tf::Quaternion myTfQuaternion(roll, yaw, -1 * pitch);
  tf::Quaternion myTfQuaternion(roll, yaw, -1 * pitch);
  valveOrientation*=myTfQuaternion;

  tf::quaternionTFToMsg(valveOrientation, v_cloud.pose.orientation);

  //Transform the valve back into it's own tf
  myListener->transformPose((std::string)target_frame, v_cloud, res.valve);


  //TODO Delete all of this and make it populate the service response and return true
  res.valve.header = req.valve.header;

  return true;
  
  //Turn the output back into a sensor_msg
//  pcl::toROSMsg(valve_cloud_aligned, output_aligned);
//  pcl::toROSMsg(valve_cloud_input, output_valve);

  //Give the output a header so that we know where it is in the world
//  output_aligned.header = recent_raw_cloud.header;
//  output_valve.header = recent_raw_cloud.header;

  //Publish
//  pub_valve_update.publish(valve);
//  pub_valve_origin.publish(output_valve);
//  pub_valve_aligned.publish(output_aligned);
  
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

}

int main (int argc, char** argv) {

  // Initialize ROS and the NodeHandle
  ros::init (argc, argv, "valve_icp");
  ros::NodeHandle nh;

  //Create a server to align the valve with the pointcloud
  ros::ServiceServer server = nh.advertiseService("request_valve_pose", valve_request);
  
  //The client to get the most recent pointcloud
  pointcloud_update_client = nh.serviceClient<gui::pointcloud>("/gui/pointcloud_update");

  //Create a TransformListener
  myListener = new(tf::TransformListener);

  //Start looking for the transform between the valve and the camera frame
  std::string pointcloud_frame, target_frame;
  nh.getParam("pointcloud_frame", pointcloud_frame);
  nh.getParam("target_frame", target_frame);
  bool found = false;
  while (found == false) {
    found = myListener->waitForTransform((std::string)pointcloud_frame, (std::string)target_frame, ros::Time(), ros::Duration(1));
  }
  
  ROS_INFO("Ready to Proceed Captain");

  // Spin
  ros::spin ();

  return 0;
}
