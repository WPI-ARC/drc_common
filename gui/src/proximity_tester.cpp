#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Transform.h"
#include "razer_hydra/Hydra.h"
#include "razer_hydra/HydraPaddle.h"

ros::Publisher pub_hydra_point;

void  hydra_calib_cb (razer_hydra::Hydra hydra){

    geometry_msgs::Point myPoint;

//    myPoint.x = hydra.paddles[1].transform.translation.x;
    myPoint.x = hydra.paddles[1].trigger * 255;
    myPoint.y = hydra.paddles[1].transform.translation.y;
    myPoint.z = hydra.paddles[1].transform.translation.z;

    pub_hydra_point.publish(myPoint);

    ros::Duration(.1).sleep();
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "proximity_test");

  //Setup everything for the publishes
  ros::NodeHandle nh;

  //Advertise the two publishers, one for the commands and one for the gui
  pub_hydra_point = nh.advertise<geometry_msgs::Point>("/feedback_devices/tacta_wrist/input", 1);

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub_hydra = nh.subscribe ("/hydra_calib", 1, hydra_calib_cb);

  //Spin Forever
  ros::spin();

  return 0;

}
