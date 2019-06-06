#include "ros/ros.h"
#include "husky_commander/AddTwoInts.h"
#include "geometry_msgs/Twist.h"


class commander{

    public:
        commander();

    private:
        bool callback(husky_commander::AddTwoInts::Request  &req,
            husky_commander::AddTwoInts::Response &res);

        ros::NodeHandle n;
        ros::Publisher pub;
        ros::ServiceServer service;
};

commander::commander(){
    service = n.advertiseService("add_two_ints", &commander::callback, this);
    pub = n.advertise<geometry_msgs::Twist>("/vel_cmd", 1, true);
}

    bool commander::callback(husky_commander::AddTwoInts::Request  &req,
            husky_commander::AddTwoInts::Response &res)
    {
        res.sum = req.a + req.b;
        ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
        ROS_INFO("sending back response: [%ld]", (long int)res.sum);

        
        geometry_msgs::Twist msg;
        msg.linear.x = req.a;
        msg.linear.y = 0;
        msg.linear.z = 0;
        msg.angular.x = 0;
        msg.angular.y = 0;
        msg.angular.z = 0;
        pub.publish(msg);

        return true;
    }


int main(int argc, char **argv)
{
  ros::init(argc, argv, "add_two_ints_server");
  commander commander;

  ROS_INFO("Ready to add two ints.");
  ros::spin();

  return 0;
}