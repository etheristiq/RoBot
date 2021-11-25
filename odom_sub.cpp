#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
// #include "sensor_msgs/LaserScan.h"
#include "nav_msgs/Odometry.h"
// #include "sensor_msgs/Inu.h"
// #include <tf/transform_broadcaster.h>

// #include <limits>                   //для обозначения inf в условии выхода из цикла

float distance=0;

void odom_msg_Callback(const nav_msgs::Odometry::ConstPtr& msg)
{
  //std::cout<<scan->ranges[0]<<std::endl;
  // std::cout<<"float_lim: "<<std::numeric_limits<float>::max()<<std::endl;
  
  // if ((scan->ranges[0])!=std::numeric_limits<float>::max()){
  //     distance=scan->ranges[0];
  // }

  std::cout<<msg->pose.pose.position<<std::endl;
  
}      

int main(int argc, char **argv)
{
  ros::init(argc, argv, "odometry_sub");
  // ros::NodeHandle p;
  ros::NodeHandle s;

  // ros::init(argc, argv, "odometry_publisher");

  // ros::NodeHandle n;
  // ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  // tf::TransformBroadcaster odom_broadcaster;

  // double x = 0.0;
  // double y = 0.0;
  // double th = 0.0;

  // double vx = 0.1;
  // double vy = -0.1;
  // double vth = 0.1;

  // ros::Publisher vel_pub = p.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::Subscriber lidar_sub = s.subscribe("odom", 1000, odom_msg_Callback);

  // std::cout<<"Init complete"<<std::endl;
  // ros::Duration(0.2).sleep();//нужно чтобы паблишер успел зарегистрироваться в росе
  
  // //ros::Rate loop_rate(10); //10 Hz

  // while (ros::ok())
  // {
  //   geometry_msgs::Twist velocity;
    
  //   if (distance>0.3){
  //       std::cout<<distance<<'\n';
  //       std::cout<<"Distance>0.2; velocity=0.1"<<std::endl;
  //       velocity.linear.x=0.1;
  //       velocity.angular.z=0;
  //       vel_pub.publish(velocity);
  //   }else{
  //       std::cout<<distance<<'\n';
  //       std::cout<<"Distance<=0.2; velocity=0"<<std::endl;
  //       velocity.linear.x=0;
  //       velocity.angular.z=0;
  //       vel_pub.publish(velocity);
  //  }

    //loop_rate.sleep(5);
    ros::Duration(0.5).sleep();

    ros::spin();
    //loop_rate.sleep();
    

    //ros::spin();
  return 0;
}
