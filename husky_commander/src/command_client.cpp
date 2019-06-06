#include "ros/ros.h"
#include "husky_commander/command.h"
#include "geometry_msgs/Twist.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "command_husky_client");
  if (argc != 2)
  {
    ROS_INFO("usage: Send 0 for forwards and 1 for backwards movement.");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<husky_commander::command>("command_husky");
  husky_commander::command srv;
  srv.request.direction = atoll(argv[1]);
  
  if (client.call(srv))
  {
    ROS_INFO("Sum: %ld", (long int)srv.response.response);
  }
  else
  {
    ROS_ERROR("Failed to call service");
    return 1;
  }

  return 0;
}