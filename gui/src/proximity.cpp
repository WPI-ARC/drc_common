#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"
#include "sensor_msgs/PointCloud2.h"

#include <pcl/filters/voxel_grid.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/ros/conversions.h>

#include "gui/pointcloud.h"
#include <feedback_devices/tacta_wrist.h>


/**
#include <cstdlib>
#include <vector>
#include <std_msgs/Float32.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/PointCloud2.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
// PCL specific includes
#include <pcl/io/pcd_io.h>
#include <pcl/registration/icp.h>
#include "gui/proximity_srv.h"
#include "gui/proximity_msg.h"
**/


#define SENSOR_RANGE .25 //Meters




//#define PROXIMITY_SENSORS 4
//#define PROXIMITY_MIN   0.1
//#define PROXIMITY_MAX   2.0
//#define PROXIMITY_DELTA 0.1
//#define PROXIMITY_POINTS ((PROXIMITY_MAX - PROXIMITY_MIN) / PROXIMITY_DELTA)

ros::Publisher pub_end_effector;
ros::Publisher pub_right_wrist;
ros::ServiceClient pointcloud_update_client;

/**
 * Odometry from Turtlebot is in the /odom frame
 *
 *
 */
void proximity_cb (geometry_msgs::Point input){

/** Turn this on when ready to try the real implementation

    //Request a Cloud from the Pointcloud Client
    sensor_msgs::PointCloud2::Ptr cloud_raw;
    gui::pointcloud pointcloud_update;
    pointcloud_update.request.voxel = true;
    pointcloud_update.request.x = .01;
    pointcloud_update.request.y = .01;
    pointcloud_update.request.z = .01;

    if (pointcloud_update_client.call(pointcloud_update)) {
      *cloud_raw = pointcloud_update.response.pointcloud;
    }
    else { ROS_ERROR("/gui/proximity.cpp:59: Pointcloud Update FAILED"); }

    //Voxel Filter the cloud
    sensor_msgs::PointCloud2 cloud;
    pcl::VoxelGrid<sensor_msgs::PointCloud2> voxel_filter;
    voxel_filter.setInputCloud(cloud_raw);
    voxel_filter.setLeafSize(.01, .01, .01);
    voxel_filter.filter(cloud);

    //Convert the cloud to something more useful
    pcl::PointCloud<pcl::PointXYZ> world;
    pcl::fromROSMsg(cloud, world);



    //Create a new cloud to store points within range
    pcl::PointCloud<pcl::PointXYZ> obstacles;

    //Add points to the cloud that are in the bounding box of the valve
    for (unsigned int i = 0; i < world.size(); i++){

        //Check if the point is within the sensor radius
        if (sqrt(pow(hydraPosition.position.x - world.points[i].x,2 ) +
                 pow(hydraPosition.position.y - world.points[i].y,2 ) +
                 pow(hydraPosition.position.z - world.points[i].z,2 )) <= SENSOR_RANGE) {

            pcl::PointXYZ point;
            point.x = world.points[i].x;
            point.y = world.points[i].y;
            point.z = world.points[i].z;

            obstacles.points.push_back(point);
        }

    }
**/


    //This is for testing
    //Assume that the hydra position is always (0, 0, 0) with an orientation that we'll work out later.

    /**
     01 = Bottom

     02 = Bottom-Front
     03 = Bottom-Front-Right
     04 = Bottom-Right
     05 = Bottom-Back-Right
     06 = Bottom-Back
     07 = Bottom-Back-Left
     08 = Bottom-Left
     09 = Bottom-Front-Left

     10 = Front
     11 = Front-Right
     12 = Right
     13 = Right-Back
     14 = Back
     15 = Back-Left
     16 = Left
     17 = Left-Front

     18 = Top-Front
     19 = Top-Front-Right
     20 = Top-Right
     21 = Top-Right-Back
     22 = Top-Back
     23 = Top-Back-Left
     24 = Top-Left
     25 = Top-Left-Front

     26 = Top



     2D Horizontal Plane
     Front = 10,11,17
     Right = 11,12,13
     Left = 15,16,17
     Back = 13,14,15

     2D Vertical Plane
     Top = 20,24,26
     Right = 4,12,20
     Left = 8,16,24
     Bottom = 1,4,8

     3D Proximity:
     Bottom = 1,2,3,4,5,6,7,8
     Front = 2,3,9,10,11,17,18,19,25
     Right = 3,4,5,11,12,13,19,20,21
     Left =  7,8,9,15,16,17,23,24,25
     Back =  5,6,7,13,14,15,21,22,23
     Top = 18,19,20,21,22,23,24,25,26

     **/

    geometry_msgs::Point hydraPosition;
    hydraPosition.x = input.x;
    hydraPosition.y = input.y;
    hydraPosition.z = input.z;

    //Create a new cloud to store points within range
    pcl::PointCloud<pcl::PointXYZ> obstacles;
    pcl::PointXYZ point;
    point.x = -.40;
    point.y = 0;
    point.z = .20;
    obstacles.push_back(point);

    double sum[26];
    double count[26];
    double r[26];

    for (int i = 0; i < 26; i++){
        sum[i] = 0;
        count[i] = 0;
        r[i] = 0;
    }

    /**
    //Try looking through just the horizontal plane
    for (unsigned int i = 10; i < 18; i++){

        sensor = i - 10;
        float minRange = (sensor * (360 / numSensors)) - ((360 / numSensors)/2);
        float maxRange = (sensor * (360 / numSensors)) + ((360 / numSensors)/2);

        ROS_INFO("Sensor: %d, Min: %f, Max: %f", i, minRange, maxRange);

        if (theta >= minRange && theta < maxRange){
            sum[i] = sqrt(pow(hydraPosition.x - obstacles.points[i].x,2 ) +
                          pow(hydraPosition.y - obstacles.points[i].y,2 ));
            count[i]++;
        }


    }
    **/

    float distance = sqrt(pow(hydraPosition.x - obstacles.points[0].x,2 ) +
                          pow(hydraPosition.y - obstacles.points[0].y,2 ) +
                          pow(hydraPosition.z - obstacles.points[0].z,2 ));

    float planeDistance = sqrt(pow(hydraPosition.x - obstacles.points[0].x,2 ) +
                          pow(hydraPosition.y - obstacles.points[0].y,2 ));

    if (distance <= SENSOR_RANGE) {

        double theta = (180/3.1415) * atan2((obstacles.points[0].y - hydraPosition.y),
                                            (obstacles.points[0].x - hydraPosition.x));

        double psi = (180/3.1415) * atan2((hydraPosition.z - obstacles.points[0].z), planeDistance);

//        ROS_INFO("\n\nTheta: %f, Psi: %f", theta, psi);

        if (psi >= 67.5){
            sum[0] += distance;
            count[0]++;
        }
        else if (psi >= 22.5 && psi < 67.5) {
            if ((theta >= 0 && theta < 22.5) || (theta <= 0 && theta > -22.5)) {
                sum[1] += distance;
                count[1]++;
            }
            else if (theta >= 22.5 && theta < 67.5) {
                sum[8] += distance;
                count[8]++;
            }
            else if (theta >= 67.5 && theta < 112.5) {
                sum[7] += distance;
                count[7]++;
            }
            else if (theta >= 112.5 && theta < 157.5) {
                sum[6] += distance;
                count[6]++;
            }
            else if (theta >= 157.5 || theta <= -157.5) {
                sum[5] += distance;
                count[5]++;
            }
            else if (theta <= -22.5 && theta > -67.5) {
                sum[2] += distance;
                count[2]++;
            }
            else if (theta <= -67.5 && theta > -112.5) {
                sum[3] += distance;
                count[3]++;
            }
            else if (theta <= -112.5 && theta > -157.5) {
                sum[4] += distance;
                count[4]++;
            }
        }
        else if ((psi >= 0 && psi < 22.5) || (psi <= 0 && psi > -22.5)) {
            if ((theta >= 0 && theta < 22.5) || (theta <= 0 && theta > -22.5)) {
                sum[9] += distance;
                count[9]++;
            }
            else if (theta >= 22.5 && theta < 67.5) {
                sum[16] += distance;
                count[16]++;
            }
            else if (theta >= 67.5 && theta < 112.5) {
                sum[15] += distance;
                count[15]++;
            }
            else if (theta >= 112.5 && theta < 157.5) {
                sum[14] += distance;
                count[14]++;
            }
            else if (theta >= 157.5 || theta <= -157.5) {
                sum[13] += distance;
                count[13]++;
            }
            else if (theta <= -22.5 && theta > -67.5) {
                sum[10] += distance;
                count[10]++;
            }
            else if (theta <= -67.5 && theta > -112.5) {
                sum[11] += distance;
                count[11]++;
            }
            else if (theta <= -112.5 && theta > -157.5) {
                sum[12] += distance;
                count[12]++;
            }
        }
        else if (psi <= -22.5 && psi > -67.5) {
            if ((theta >= 0 && theta < 22.5) || (theta <= 0 && theta > -22.5)) {
                sum[17] += distance;
                count[17]++;
            }
            else if (theta >= 22.5 && theta < 67.5) {
                sum[24] += distance;
                count[24]++;
            }
            else if (theta >= 67.5 && theta < 112.5) {
                sum[23] += distance;
                count[23]++;
            }
            else if (theta >= 112.5 && theta < 157.5) {
                sum[22] += distance;
                count[22]++;
            }
            else if (theta >= 157.5 || theta <= -157.5) {
                sum[21] += distance;
                count[21]++;
            }
            else if (theta <= -22.5 && theta > -67.5) {
                sum[18] += distance;
                count[18]++;
            }
            else if (theta <= -67.5 && theta > -112.5) {
                sum[19] += distance;
                count[19]++;
            }
            else if (theta <= -112.5 && theta > -157.5) {
                sum[20]+= distance;
                count[20]++;
            }
        }
        else if (psi <= -67.5){
            sum[25] += distance;
            count[25]++;
        }

        //Output the result of looking through the horizonal plane
        for (unsigned int i = 0; i < 26; i++){
            if (count[i] != 0){ r[i] = (SENSOR_RANGE - (sum[i]/count[i])) / SENSOR_RANGE; }
            else { r[i] = 0; }
        }

        //Calculate Outputs of the Tactors
//        3D Proximity:
//        Bottom = 1,2,3,4,5,6,7,8
//        Front = 2,3,9,10,11,17,18,19,25
//        Right = 3,4,5,11,12,13,19,20,21
//        Left =  7,8,9,15,16,17,23,24,25
//        Back =  5,6,7,13,14,15,21,22,23
//        Top = 18,19,20,21,22,23,24,25,26

        double bottom = r[0]*255 +
                       (r[1] + r[3] + r[5] + r[7]) * 168 +
                       (r[2] + r[4] + r[6] + r[8]) * 84;

        double front =  r[9]*255 +
                       (r[10] + r[16] + r[17] + r[1]) * 168 +
                       (r[2] + r[8] + r[18] + r[24]) * 84;

        double right =  r[11]*255 +
                       (r[10] + r[12] + r[19] + r[3]) * 168 +
                       (r[2] + r[4] + r[18] + r[20]) * 84;

        double left =  r[15]*255 +
                       (r[14] + r[16] + r[23] + r[7]) * 168 +
                       (r[22] + r[24] + r[6] + r[8]) * 84;

        double back =  r[13]*255 +
                       (r[12] + r[14] + r[21] + r[5]) * 168 +
                       (r[4] + r[6] + r[20] + r[22]) * 84;

        double top =  r[25]*255 +
                       (r[19] + r[23] + r[17] + r[21]) * 168 +
                       (r[18] + r[20] + r[22] + r[24]) * 84;

        if (top > 255) top = 255;
        if (right > 255) right = 255;
        if (left > 255) left = 255;
        if (bottom > 255) bottom = 255;
        if (front > 255) front = 255;
        if (back > 255) back = 255;

        ROS_INFO("-------------------");
        ROS_INFO("     [ %d ]\n", (int)front);
        ROS_INFO("     [ %d ]", (int)top);
        ROS_INFO("[ %d ]    [ %d ]", (int)left, (int)right);
        ROS_INFO("     [ %d ]\n", (int)bottom);
        ROS_INFO("     [ %d ]", (int)back);

        feedback_devices::tacta_wrist wrist;
        wrist.top = top;
        wrist.right = right;
        wrist.left = left;
        wrist.bottom = bottom;
        wrist.front = front;
        wrist.back = back;

        pub_right_wrist.publish(wrist);

    }




}

int main(int argc, char **argv) {
  ros::init(argc, argv, "proximity");

  //Setup everything for the publishes
  ros::NodeHandle nh;

  //Advertise the two publishers, one for the commands and one for the gui
  pub_end_effector = nh.advertise<visualization_msgs::MarkerArray>("/gui/proximity/end_effector", 1);

  //Advertise the right wrist
  pub_right_wrist = nh.advertise<feedback_devices::tacta_wrist>("/feedback_devices/tacta_wrist/input", 1);

  //The client to get the most recent pointcloud
  pointcloud_update_client = nh.serviceClient<gui::pointcloud>("/gui/pointcloud_update");

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub_hydra = nh.subscribe ("/gui/proximity/input", 1, proximity_cb);

  //Spin Forever
  ros::spin();

  return 0;

}
