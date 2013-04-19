#!/usr/bin/env python
import roslib; roslib.load_manifest('perception_pkg')
import rospy
from std_msgs.msg import Float32
from perception_pkg.srv import *

class Perception:
    def __init__(self):
        self.pub = rospy.Publisher('robotstate', Float32)
        rospy.init_node('perception')
        rospy.Subscriber('/sensor_pkg/collision_map', Float32, self.sensor_data_callback)
        rospy.Service('valve_pos',valve_pos,self.handle_valve_pos_service)
        print "Perception node says: Ready to crunch some sensor data!"
        rospy.spin()
        
    def sensor_data_callback(self,incoming):
        print "Perception pkg says: Incoming data is "+str(incoming.data)
        self.pub.publish(7357.1123)

    def handle_valve_pos_service(self,incoming):
        print "Perception pkg says: valve position was sent as "+str(incoming.request)
        return valve_posResponse(1)
        

if __name__ == '__main__':
    sensor_data_cruncher = Perception()
    # try:
    #     publish()
    # except rospy.ROSInterruptException: pass
