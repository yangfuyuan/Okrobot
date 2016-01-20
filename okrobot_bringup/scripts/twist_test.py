#!/usr/bin/env python
# license removed for brevity
import rospy
from geometry_msgs.msg import Twist

def Twist_test():
   rospy.init_node('twist_test', anonymous=True)
   pub = rospy.Publisher('cmd_vel_mux/input/teleop', Twist, queue_size=10)

   rate = rospy.Rate(10) # 10hz
   while not rospy.is_shutdown():

        cmdvel_ = Twist()
        cmdvel_.linear.x = 0.5
        cmdvel_.linear.y = 0.0
        cmdvel_.linear.z = 0.0
        cmdvel_.angular.x = 0.0
        cmdvel_.angular.y = 0.0
        cmdvel_.angular.z = 0.5
        rospy.loginfo("liner_speed=%f anglular_speed=%f" % (cmdvel_.linear.x, cmdvel_.angular.z))
        pub.publish(cmdvel_)

        rate.sleep()

if __name__ == '__main__':
    try:
       Twist_test()
    except rospy.ROSInterruptException:
       pass
