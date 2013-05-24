#!/usr/bin/env python

#   Calder Phillips-Grafflin - WPI/ARC Lab
#
#   Generic fixed TF broadcaster
#
#   Given a root frame and a target frame,
#   this broadcasts a transform using the
#   provided values for translation and
#   orientation.

import roslib; roslib.load_manifest('wpi_drc_sim')
import rospy
import tf

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    QUESTION = '\033[90m'
    FAIL = '\033[91m'
    CYAN = '\033[96m'
    BOLD = '\033[1m'
    ENDC = '\033[0m'

class Generic_TF_Broadcaster:

    def __init__(self, target_frame, root_frame, translation, orientation, rate):
        self.target_frame = target_frame
        self.root_frame = root_frame
        self.rate = rate
        self.tx = translation[0]
        self.ty = translation[1]
        self.tz = translation[2]
        self.rx = orientation[0]
        self.ry = orientation[1]
        self.rz = orientation[2]
        self.rw = orientation[3]
        self.broadcaster = tf.TransformBroadcaster()
        rospy.loginfo(bcolors.OKGREEN + "[Floating Kinect Broadcaster] Running..." + bcolors.ENDC)
        rate = rospy.Rate(self.rate)
        while not rospy.is_shutdown():
            rospy.loginfo("Publishing Transform ... ")
            t = rospy.Time.now()
            self.broadcaster.sendTransform((self.tx, self.ty, self.tz), (self.rx, self.ry, self.rz, self.rw), t, self.target_frame, self.root_frame)
            self.broadcaster.sendTransform((0.031, 0, 0.103), (0, 0, 0, 1), t, "/kinect_link", self.target_frame)
            self.broadcaster.sendTransform((0, 0.018, 0), (0, 0, 0, 1), t, "/kinect_depth_frame", "/kinect_link")
            self.broadcaster.sendTransform((0, 0, 0), (-0.013706055221903412, 0.013706055221903412, 0.0001878912528687704, 0.9998121087471312), t, "/kinect_depth_optical_frame", "/kinect_depth_frame")
            self.broadcaster.sendTransform((0, -.005, 0), (0, 0, 0, 1), t, "/kinect_rgb_frame", "/kinect_link")
            self.broadcaster.sendTransform((0, 0, 0), (-0.013706055221903412, 0.013706055221903412, 0.0001878912528687704, 0.9998121087471312), t, "/kinect_rgb_optical_frame", "/kinect_rgb_frame")
            rate.sleep()

def load_params():
    root_frame = rospy.get_param("~root_frame", "base_link")
    target_frame = rospy.get_param("~target_frame", "generic_frame")
    rate = rospy.get_param("~rate", 10.0)
    tx = rospy.get_param("~tx", 0.0)
    ty = rospy.get_param("~ty", 0.0)
    tz = rospy.get_param("~tz", 0.0)
    rx = rospy.get_param("~rx", 0.0)
    ry = rospy.get_param("~ry", 0.0)
    rz = rospy.get_param("~rz", 0.0)
    rw = rospy.get_param("~rw", 1.0)
    translation = [tx, ty, tz]
    orientation = [rx, ry, rz, rw]
    return [target_frame, root_frame, translation, orientation, rate]

if __name__ == "__main__":
    rospy.init_node("generic_floating_kinect_broadcaster")
    rospy.loginfo(bcolors.HEADER + bcolors.BOLD + "[Floating Kinect Broadcaster] Starting the TF broadcaster..." + bcolors.ENDC)
    #Get the parameters from the server
    [target_frame, root_frame, translation, orientation, rate] = load_params()
    #Print the starting parameters to the screen
    rospy.loginfo(bcolors.HEADER + bcolors.BOLD + "[Floating Kinect Broadcaster] Starting with target frame: " + target_frame + bcolors.ENDC)
    rospy.loginfo(bcolors.HEADER + bcolors.BOLD + "[Floating Kinect Broadcaster] Starting with root frame: " + root_frame + bcolors.ENDC)
    rospy.loginfo(bcolors.HEADER + bcolors.BOLD + "[Floating Kinect Broadcaster] Starting with translation: " + str(translation) + bcolors.ENDC)
    rospy.loginfo(bcolors.HEADER + bcolors.BOLD + "[Floating Kinect Broadcaster] Starting with orientation: " + str(orientation) + bcolors.ENDC)
    rospy.loginfo(bcolors.HEADER + bcolors.BOLD + "[Floating Kinect Broadcaster] Starting with update rate: " + str(rate) + bcolors.ENDC)
    Generic_TF_Broadcaster(target_frame, root_frame, translation, orientation, rate)
