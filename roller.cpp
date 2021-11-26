#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

#include <limits>                   //для обозначения inf в условии выхода из цикла

float distance=0;

void laser_msg_Callback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
  //std::cout<<scan->ranges[0]<<std::endl;
  std::cout<<"float_lim: "<<std::numeric_limits<float>::max()<<std::endl;
  
  //if ((scan->ranges[0])!=std::numeric_limits<float>::max()){
  if ((scan->ranges[0])<100.0){
      distance=scan->ranges[0];
  }
  
}      

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rolla");
  ros::NodeHandle p;
  ros::NodeHandle s;

  ros::Publisher vel_pub = p.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::Subscriber lidar_sub = s.subscribe("scan", 1000, laser_msg_Callback);

  geometry_msgs::Twist velocity;
  
  std::cout<<"Init complete"<<std::endl;
  ros::Duration(0.2).sleep();//нужно чтобы паблишер успел зарегистрироваться в росе
  
  //ros::Rate loop_rate(10); //10 Hz

  while (ros::ok())
  {
    
    
    if (distance>0.3){
        std::cout<<distance<<'\n';
        std::cout<<"Distance>0.2; velocity=0.1"<<std::endl;
        velocity.linear.x=0.1;
        velocity.angular.z=0;
        vel_pub.publish(velocity);
    }else{
        std::cout<<distance<<'\n';
        std::cout<<"Distance<=0.2; velocity=0"<<std::endl;
        velocity.linear.x=0;
        velocity.angular.z=0;
        vel_pub.publish(velocity);
    }

    //loop_rate.sleep(5);
    ros::Duration(0.5).sleep();

    ros::spinOnce();
    //loop_rate.sleep();
    
  }
    //ros::spin();
  return 0;
}
