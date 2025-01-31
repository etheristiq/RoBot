#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include "geometry_msgs/Twist.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Quaternion.h>
#include <math.h> 

double theta;


#define TOL 0.01
#define K 1.5

void imu_cb(const nav_msgs::Odometry::ConstPtr& odom_msg){
    
    float t1,t2;
    
    //std::cout<<odom_msg->pose.pose.position<<std::endl;
    
    t1 +=2.0*(odom_msg->pose.pose.orientation.w*odom_msg->pose.pose.orientation.z + odom_msg->pose.pose.orientation.x*odom_msg->pose.pose.orientation.y);
    t2 +=1.0-2.0*(pow(odom_msg->pose.pose.orientation.y,2) + pow(odom_msg->pose.pose.orientation.z,2));
    
    theta=atan2(t1,t2);
    
    
    std::cout<<theta<<std::endl;
}




int main(int argc, char** argv){
    ros::init(argc, argv, "odometry_publisher");

    //ros::NodeHandle n;
    ros::NodeHandle s;
    //ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
    ros::Subscriber odom_sub = s.subscribe("odom", 1000, imu_cb);
    //tf::TransformBroadcaster odom_broadcaster;
    ros::NodeHandle p;
    ros::Publisher vel_pub = p.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    
    geometry_msgs::Twist velocity;

//     double x = 0.0;
//     double y = 0.0;
//     double th = 0.0;
// 
//     double vx = 0.1;
//     double vy = -0.1;
//     double vth = 0.1;

    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    last_time = ros::Time::now();

    ros::Duration(0.2).sleep();
    
    ros::Rate r(1.0);
    while(s.ok()){

        ros::spinOnce();               // check for incoming messages
        current_time = ros::Time::now();

//         if (theta>1.5708){
//             std::cout<<"right"<<std::endl;
//             velocity.linear.x=0.05;
//             velocity.angular.z=abs(1.5708-theta)*0.2;
//             vel_pub.publish(velocity);
//         }

        velocity.linear.x=0.05;
        velocity.angular.z=(-theta)*K;
        vel_pub.publish(velocity);
        
//         compute odometry in a typical way given the velocities of the robot
//         double dt = (current_time - last_time).toSec();
//         double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
//         double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
//         double delta_th = vth * dt;
// 
//         x += delta_x;
//         y += delta_y;
//         th += delta_th;

//         since all odometry is 6DOF we'll need a quaternion created from yaw
//         geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);
// 
//         first, we'll publish the transform over tf
//         geometry_msgs::TransformStamped odom_trans;
//         odom_trans.header.stamp = current_time;
//         odom_trans.header.frame_id = "odom";
//         odom_trans.child_frame_id = "base_link";
// 
//         odom_trans.transform.translation.x = x;
//         odom_trans.transform.translation.y = y;
//         odom_trans.transform.translation.z = 0.0;
//         odom_trans.transform.rotation = odom_quat;
// 
//         send the transform
//         odom_broadcaster.sendTransform(odom_trans);
// 
//         next, we'll publish the odometry message over ROS
//         nav_msgs::Odometry odom;
//         odom.header.stamp = current_time;
//         odom.header.frame_id = "odom";
// 
//         set the position
//         odom.pose.pose.position.x = x;
//         odom.pose.pose.position.y = y;
//         odom.pose.pose.position.z = 0.0;
//         odom.pose.pose.orientation = odom_quat;
// 
//         set the velocity
//         odom.child_frame_id = "base_link";
//         odom.twist.twist.linear.x = vx;
//         odom.twist.twist.linear.y = vy;
//         odom.twist.twist.angular.z = vth;
// 
//         publish the message
//         odom_pub.publish(odom);

        last_time = current_time;
        r.sleep();
    }
}
