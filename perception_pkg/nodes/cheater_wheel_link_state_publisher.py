#!/usr/bin/env python
# Bener Suay, December 2012
# benersuay@wpi.edu
#
# This script subscribes to Gazebo, get's the wheel's position from the simulator without any sensing (hence the name cheater), transforms the coordinates and publishes.
#

import roslib; 
roslib.load_manifest('gazebo_msgs')
roslib.load_manifest('std_msgs')
roslib.load_manifest('sensor_msgs')
roslib.load_manifest('geometry_msgs')
roslib.load_manifest('tf_conversions')
roslib.load_manifest('kdl')

import rospy
from std_msgs.msg import String
from gazebo_msgs.msg import LinkStates
from gazebo_msgs.msg import LinkState
from geometry_msgs.msg import Pose
from geometry_msgs.msg import PoseStamped
import tf_conversions.posemath as pm
import PyKDL

from numpy import *


class WheelPosePublisher:
    def __init__(self):
        self.sourceLinkName = 'wheel::base' # We want to have the pose of this link
        self.targetLinkName = 'pr2::torso_lift_link' # We want the target link to be defined in this frame_id
        rospy.init_node('cheater', anonymous=False)
        rospy.Subscriber('/gazebo/link_states', LinkStates, self.link_states_callback)
        self.wPub = rospy.Publisher('wheel_pose',PoseStamped)
        rospy.spin()
        pass

    def link_states_callback(self,links):
        self.source = LinkState() # This is wheel's pose in world coordinate frame
        self.target = LinkState() # This is the frame in which we want to get the pose of the wheel (note: pose and orientation of this frame is defined in world coordinate system in gazebo)
        for l in range(len(links.name)):
            if(links.name[l] == self.sourceLinkName):
                self.source.link_name = links.name[l]
                self.source.pose = links.pose[l] # Position and Orientation
                self.source.twist = links.twist[l] # Lin and Ang Velocity
                self.source.reference_frame = 'gazebo' # Note that this actually is not a tf. I made it up to mark that this reference frame defined in gazebo's world coordinates.
            if(links.name[l] == self.targetLinkName):
                self.target.link_name = links.name[l]
                self.target.pose = links.pose[l]
                self.target.twist = links.twist[l]
                self.target.reference_frame = 'gazebo' # Note that this actually is not a tf. I made it up to mark that this reference frame defined in gazebo's world coordinates.

        self.model_state_publisher()
            

    # Publish the wheel's state in "toFrameId" after converting
    def model_state_publisher(self):
        #############
        targetFrame = PyKDL.Frame(PyKDL.Rotation.Quaternion(self.target.pose.orientation.x,self.target.pose.orientation.y,self.target.pose.orientation.z,self.target.pose.orientation.w), PyKDL.Vector(self.target.pose.position.x,self.target.pose.position.y,self.target.pose.position.z))

        targetFrameMatrix = pm.toMatrix(targetFrame)

        sourceFrame = PyKDL.Frame(PyKDL.Rotation.Quaternion(self.source.pose.orientation.x,self.source.pose.orientation.y,self.source.pose.orientation.z,self.source.pose.orientation.w),PyKDL.Vector(self.source.pose.position.x,self.source.pose.position.y,self.source.pose.position.z))
        
        pose = pm.toMsg(pm.fromMatrix(linalg.inv(targetFrameMatrix))*sourceFrame)
        
        poseStamped = PoseStamped()
        poseStamped.pose = pose
        poseStamped.header.stamp = rospy.get_rostime()
        poseStamped.header.frame_id = '/'+self.targetLinkName[5:len(self.targetLinkName)] # This strips 'pr2::' from the frame_id string
        self.wPub.publish(poseStamped)

if __name__ == '__main__':
    wpp = WheelPosePublisher()

