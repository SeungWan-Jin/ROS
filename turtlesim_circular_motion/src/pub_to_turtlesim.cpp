#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim_circular_motion/circularMotion.h"

geometry_msgs::Twist msg;

void letCmdPub(const turtlesim_circular_motion::circularMotion::ConstPtr& inputMsg)
{
	msg.linear.x = inputMsg->velocity;
	msg.angular.z = inputMsg->velocity / inputMsg->radius;
	if(inputMsg->direction == "CW") msg.angular.z *= -1;

	ROS_INFO("\nlinear\n   x: %f\n   y: %f\n   z: %f\nangular\n   x: %f\n   y: %f\n   z: %f\n", msg.linear.x, msg.linear.y, msg.linear.z, msg.angular.x, msg.angular.y, msg.angular.z);
}

int main(int argc, char **argv)
{
	// ROS node with a give name "pub_to_turtlesim"
	ros::init(argc, argv, "pub_to_turtlesim");
	ros::NodeHandle n;

	ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);
	// The subscribe() call is how you tell ROS that you want to receive messages on a given topic.
	// when /cmd_input topie subscirbed, messages are passed to a call back function letCmdPub.
	ros::Subscriber sub = n.subscribe("/cmd_input", 1, letCmdPub);
	ros::Rate hz(10);

	ROS_INFO("Waiting...");
	while(ros::ok())
	{
		cmd_vel_pub.publish(msg);
		ros::spinOnce();
		hz.sleep();
	}
	return 0;
}