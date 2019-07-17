#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Imu
from geometry_msgs.msg import Pose ,Quaternion
import tf

rospy.init_node('odom_pub')
fixed_frame = '/odom'
br = tf.TransformBroadcaster()
imu = Imu()
pose = Pose()
ori = Quaternion()


def IMU_callback(data):
    global imu
    imu = data


position = rospy.Publisher('robot_pose', Pose, queue_size=10)
rate = rospy.Rate(10)
rospy.Subscriber('/imu/data', Imu, IMU_callback)


def run():
    pose.orientation = imu.orientation
    pose.position = [0, 1, 0]
    position.publish(pose)
    br.sendTransform(pose.position, (imu.orientation.x,imu.orientation.y,imu.orientation.z,imu.orientation.w), rospy.Time.now(), '/base_link', fixed_frame)
    print(pose.position)
    print(imu.orientation)
    rate.sleep()
    rospy.spin()


if __name__ == '__main__':
    run()
