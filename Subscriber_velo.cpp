#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"


#include <string>
#include <sstream>

float l = 100.0;

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
  //std::cout << scan->ranges[0]<<std::endl;
  std::cout<<l<<std::endl;
  l = scan->ranges[0];
  
  //ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "velo_dri");
  ros::NodeHandle n,s;
  
  ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  ros::Subscriber sub = s.subscribe("/scan", 1000, chatterCallback);

  geometry_msgs::Twist msg;
  std::cout << "We've started\n"<< l << std::endl;
  
  while (l > 0.30){
  	
  	msg.linear.x = 0.1;
  	vel_pub.publish(msg);
  	ros::spinOnce();
 	ros::Duration(0.1).sleep();
  }
  
  std::cout << "We've finished\n";
  
  msg.linear.x = 0;
  vel_pub.publish(msg);
  ros::spinOnce();
  
  std::cout << "We've sent stop cmd\n";
  

   
  // std::cout << "Node is initialised" << std::endl;
  //ros::Subscriber sub = n.subscribe("/scan", 10, chatterCallback);
  

  
  
  

  return 0;
}
