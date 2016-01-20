#!/usr/bin/env python


#Python client library for ROS
import rospy
import sys

from okrobot_bringup.msg import speed
from std_msgs.msg import Float32



class TWO_Class():



	def __init__(self):
		print "Initializing TWO Class"

#######################################################################################################################
		#Sensor variables



		self.speed = speed()


#######################################################################################################################
#Subscribers and Publishers

		#Publisher for left and right wheel encoder values
		self._wheel_speed = rospy.Publisher('wheel_speed',speed,queue_size = 10)


#######################################################################################################################
#Speed subscriber
		self._left_motor_speed = rospy.Subscriber('left_wheel_speed',Float32,self._Update_Left_Speed)

		self._right_motor_speed = rospy.Subscriber('right_wheel_speed',Float32,self._Update_Right_Speed)


#######################################################################################################################
	def _Update_Left_Speed(self, left_speed):

		self.speed.left = left_speed.data
		rospy.loginfo("left_speed=%f right_speed=%f" % (self.speed.left, self.speed.right))
		self._wheel_speed.publish(self.speed)


#######################################################################################################################################################3


	def _Update_Right_Speed(self, right_speed):

		self.speed.right = right_speed.data
		rospy.loginfo("left_speed1=%f right_speed1=%f" % (self.speed.left, self.speed.right))
		self._wheel_speed.publish(self.speed)







##########################################################################################


#######################################################################################################################



if __name__ =='__main__':

	rospy.init_node('two_to_one',anonymous=True)
	TWO_Class()

	rospy.spin()



#######################################################################################################################


