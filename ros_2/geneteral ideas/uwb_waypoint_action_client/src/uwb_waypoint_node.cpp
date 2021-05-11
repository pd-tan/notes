#include <rclcpp/rclcpp.hpp>
#include "uwb_waypoint_action_client/uwb_waypoint_client.hpp"

int main(int argc, char **argv) {
  // setup ROS node
  rclcpp::init(argc, argv);

  std::shared_ptr<uwb_waypoint_client::FibonacciActionClient> messenger =
      std::make_shared<uwb_waypoint_client::FibonacciActionClient>();

  // publish robot state at 50Hz while listening to twist commands
  rclcpp::Rate rate(50);
  while (true) {
    rclcpp::spin_some(messenger);
    rate.sleep();
  }

  return 0;
}