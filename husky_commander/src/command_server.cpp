#include "ros/ros.h"
#include "husky_commander/command.h"
#include "geometry_msgs/Twist.h"
#include <sstream>



class commander{

  public:
    int64_t callback(husky_commander::command::direction  &req,
          husky_commander::command::response &res)
  {
    res.response = req.direction;
  
    ROS_INFO("request: x=%ld, y=%ld", (long int)req.direction);
    ROS_INFO("sending back response: [%ld]", (long int)res.response);
    

    return atoll(req.direction);
  }

};

int main(int argc, char **argv)
  {
    ros::init(argc, argv, "command_husky");
    ros::NodeHandle n;

    commander dir;
    
    ros::ServiceServer service = n.advertiseService("command_husky", &commander::callback, &dir);

    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    geometry_msgs::Twist msg;
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
      msg.linear.x = dir;
      msg.linear.y = 0;
      msg.linear.z = 0;
      msg.angular.x = 0;
      msg.angular.y = 0;
      msg.angular.z = 0;
      pub.publish(msg);

      ros::spinOnce();
    }
    

    return 0;
  }

