#!/usr/bin/env python


#Python client library for ROS
import rospy
import sys

from sensor_msgs.msg import Imu

#data = Imu()



#######################################################################################################################
def imucallback(data):
	data.header.frame_id
	data.orientation.x
	data.orientation.y
	data.orientation.z
	data.orientation.w

	rospy.loginfo("id=%s x=%f y=%f z=%f w=%f" %
				  (data.header.frame_id, data.orientation.x, data.orientation.y, data.orientation.z, data.orientation.w))


		
def Imusub():
	rospy.init_node('IMU_ros',anonymous=True)
	rospy.Subscriber('imu/data',Imu,imucallback)

	rospy.spin()



#######################################################################################################################

if __name__ =='__main__':
	Imusub()



#######################################################################################################################


