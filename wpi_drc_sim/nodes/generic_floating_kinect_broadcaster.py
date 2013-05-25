#!/usr/bin/env python

#   Calder Phillips-Grafflin - WPI/ARC Lab
#   
#
#   Generic fixed TF broadcaster 
#   (modified for publishing floating Kinect TFs)
#   modded by: Nick Alunni (nalunni@wpi.edu) and,
#              Bener Suay (benersuay@wpi.edu)
# 
#   Given a root frame and a target frame,
#   this broadcasts a transform using the
#   provided values for translation and
#   orientation.

import roslib; roslib.load_manifest('wpi_drc_sim')
import rospy
import tf
from urdf import URDF
from urdf import Joint
from urdf import Pose
import sys
from numpy import *

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


class Kinect_TF_Broadcaster:

    def __init__(self, target_frame, root_frame, translation, orientation, rate, floating_kinect_description):
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

        # Joint() and Pose() classes are defined in urdf.py
        # See urdf.py for their attributes and methods
        self.first_joint = Joint("first_joint",self.root_frame,self.target_frame,"fixed")
        self.first_joint.origin = Pose()
        self.first_joint.origin.position = [self.tx, self.ty, self.tz]
        self.first_joint.origin.rotationQuat = [self.rx, self.ry, self.rz, self.rw]
        self.joints = [self.first_joint]

        #self.param_name = my_description_parameter
        rospy.loginfo(bcolors.OKGREEN + "[Floating Kinect Broadcaster] Running..." + bcolors.ENDC)
        rate = rospy.Rate(self.rate)

        # 1) Parse the floating_kinect.urdf
        floating_kinect = URDF().parse(floating_kinect_description)

        # 2) Get the transforms we need to publish
        for (jname, joint) in floating_kinect.joints.items():

            # 3) Convert the RPY axis-angle representation values into Quaternions
            joint.origin.rotationQuat = self.axisToQuaternion(joint.origin.rotation)
            
            # 4) Append in the list of joints (i.e. TFs) to publish
            self.joints.append(joint)            

        while not rospy.is_shutdown():
            rospy.loginfo("Publishing Transform ... ")
            t = rospy.Time.now()

            # This is how a broadcaster is called
            #
            # self.broadcaster.sendTransform((self.tx, self.ty, self.tz), (self.rx, self.ry, self.rz, self.rw), t, self.target_frame, self.root_frame)

            for j in self.joints:
                # If you want more info about the joints uncomment the following block
                #
                # print j.name
                # print j.origin.position
                # print j.origin.rotation
                # print j.origin.rotationQuat
                # print j.parent
                # print j.child
                #
                # Publish the TFs in the list
                self.broadcaster.sendTransform((j.origin.position[0], j.origin.position[1], j.origin.position[2]), (j.origin.rotationQuat[0], j.origin.rotationQuat[1], j.origin.rotationQuat[2], j.origin.rotationQuat[3]), t, j.child, j.parent)
            rate.sleep()

    def axisToQuaternion(self, PHI):
        
        # See Simultaneous Orthogonal Rotation Angle definition here: 
        #
        # http://en.wikipedia.org/wiki/Axis%E2%80%93angle_representation
        #
        # Also see the explanation of the conversion from SORA to Quaternion here:
        #
        # http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/
        #
        # I'm using wikipedia's terminology.
        #
        # Calculate phi
        angle = pow((pow(PHI[0],2)+pow(PHI[1],2)+pow(PHI[2],2)),0.5)
        if( angle != 0 ):
            # calculate v vector
            vx = (PHI[0]/angle)
            vy = (PHI[1]/angle)
            vz = (PHI[2]/angle)
            
            # normalization factor
            magnitude = pow((pow(vx,2)+pow(vy,2)+pow(vz,2)),0.5)
            
            # From here on it's taken from euclideanspace.com
            s = sin(angle/2)

            # normalize and calculate
            x = (vx/magnitude)*s
            y = (vy/magnitude)*s
            z = (vz/magnitude)*s
            w = cos(angle/2)
            return [x,y,z,w]
        else:
            return [0,0,0,1]

def load_params():
    root_frame = rospy.get_param("~root_frame", "base_link")
    target_frame = rospy.get_param("~target_frame", "generic_frame")
    rate = rospy.get_param("~rate", 10.0)
    floating_kinect_description = rospy.get_param("floating_kinect_description")
    tx = rospy.get_param("~tx", 0.0)
    ty = rospy.get_param("~ty", 0.0)
    tz = rospy.get_param("~tz", 0.0)
    rx = rospy.get_param("~rx", 0.0)
    ry = rospy.get_param("~ry", 0.0)
    rz = rospy.get_param("~rz", 0.0)
    rw = rospy.get_param("~rw", 1.0)
    translation = [tx, ty, tz]
    orientation = [rx, ry, rz, rw]
    return [target_frame, root_frame, translation, orientation, rate, floating_kinect_description]

if __name__ == "__main__":
    rospy.init_node("generic_floating_kinect_broadcaster")
    rospy.loginfo(bcolors.HEADER + bcolors.BOLD + "[Floating Kinect Broadcaster] Starting the TF broadcaster..." + bcolors.ENDC)
    #Get the parameters from the server
    [target_frame, root_frame, translation, orientation, rate, floating_kinect_description] = load_params()
    #Print the starting parameters to the screen
    rospy.loginfo(bcolors.HEADER + bcolors.BOLD + "[Floating Kinect Broadcaster] Starting with target frame: " + target_frame + bcolors.ENDC)
    rospy.loginfo(bcolors.HEADER + bcolors.BOLD + "[Floating Kinect Broadcaster] Starting with root frame: " + root_frame + bcolors.ENDC)
    rospy.loginfo(bcolors.HEADER + bcolors.BOLD + "[Floating Kinect Broadcaster] Starting with translation: " + str(translation) + bcolors.ENDC)
    rospy.loginfo(bcolors.HEADER + bcolors.BOLD + "[Floating Kinect Broadcaster] Starting with orientation: " + str(orientation) + bcolors.ENDC)
    rospy.loginfo(bcolors.HEADER + bcolors.BOLD + "[Floating Kinect Broadcaster] Starting with update rate: " + str(rate) + bcolors.ENDC)

    Kinect_TF_Broadcaster(target_frame, root_frame, translation, orientation, rate, floating_kinect_description)
