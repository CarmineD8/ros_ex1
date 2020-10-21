#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "turtlesim/Kill.h"
#include "turtlesim/Spawn.h"
#include <sstream>
#include <iostream>


//TODO declare the publisher as global

void subscriberCallback(const turtlesim::Pose::ConstPtr& pose_msg)
{
   //TODO! Use the pose_msg to control the turtle (i.e., to publish the correct velocity command)
    
    if ((pose_msg->y >8.9))
    {
	ros::shutdown();
    }
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "turtlebot_controller");
  ros::NodeHandle n;

  ros::ServiceClient client1 = n.serviceClient<turtlesim::Kill>("/kill");
  ros::ServiceClient client2 = n.serviceClient<turtlesim::Spawn>("/spawn");

  
  turtlesim::Kill srv1;
  srv1.request.name = "turtle1";

  client1.call(srv1);

  turtlesim::Spawn srv2;

  srv2.request.x=5.0;
  srv2.request.y=5.0;
  srv2.request.theta=0.0;
  srv2.request.name="rt_turtle";

  client2.call(srv2);
  //TODO! call the service clear (optional) and rt_turtle/teleport_absolute
  ros::Subscriber pose_sub = n.subscribe("/rt_turtle/pose", 1000, subscriberCallback);
  //TODO Initialize the publisher

  ros::spin();

  return 0;
}
