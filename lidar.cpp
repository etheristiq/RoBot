#include "ros/ros.h"

#include "sensor_msgs/LaserScan.h"


void laser_msg_Callback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
  std::cout<<scan->ranges[0]<<std::endl;
}                  

int main(int argc, char **argv)
{

  ros::init(argc, argv, "lidar_listener"); 

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("scan", 1000, laser_msg_Callback);

  ros::spin();

  return 0;

}
