#include <ros/ros.h>

#include "sensor_msgs/LaserScan.h"
#include "std_msgs/Float32.h"
#include "std_msgs/String.h"

class Min_distance
{
public:
  Min_distance()
  {
    //Topic you want to publish
    pub_ = n_.advertise<std_msgs::Float32>("/min_distance", 1);

    //Topic you want to subscribe
    sub_ = n_.subscribe("base_scan", 1000, &Min_distance::callback,this);
  }

  void callback(const sensor_msgs::LaserScan::ConstPtr& msg)
  {
    ros::NodeHandle n2;
    int i=0;
    float anglemax     = msg->angle_max;
    float anglemin     = msg->angle_min;
    float angleinc     = msg->angle_increment;
    float length       = (anglemax-anglemin)/angleinc;
    int intlength      = int(length)+1;
    float min_distance = msg->ranges[0];

    for (i=0; i<intlength;i++){
     if(min_distance>msg->ranges[i]){
      min_distance=msg->ranges[i];
     }
    }

    std_msgs::Float32 msg2;
    msg2.data= min_distance;
    pub_.publish(msg2);
    ROS_INFO("MINIMUM DISTANCE: %f", msg2.data);
 }

private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "Mini");

  //Create an object of class SubscribeAndPublish that will take care of everything
  Min_distance SAPObject;

  ros::spin();

  return 0;
}

