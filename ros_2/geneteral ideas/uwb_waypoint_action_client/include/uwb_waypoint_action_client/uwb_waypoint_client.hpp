#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>

#include "action_tutorials_interfaces/action/fibonacci.hpp"
#include <geometry_msgs/msg/twist.hpp>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"

namespace uwb_waypoint_client {
class FibonacciActionClient : public rclcpp::Node {
 public:
  using Fibonacci = action_tutorials_interfaces::action::Fibonacci;
  using GoalHandleFibonacci = rclcpp_action::ClientGoalHandle<Fibonacci>;
  explicit FibonacciActionClient();
  void send_goal(int fibo_order);

 private:

  rclcpp_action::Client<Fibonacci>::SharedPtr client_ptr_;
  rclcpp::TimerBase::SharedPtr timer_;

  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr
      motion_cmd_subscription_;
  void TwistCmdCallback(const geometry_msgs::msg::Twist::SharedPtr msg);

  void goal_response_callback(
      std::shared_future<GoalHandleFibonacci::SharedPtr> future);
  void feedback_callback(
      GoalHandleFibonacci::SharedPtr,
      const std::shared_ptr<const Fibonacci::Feedback> feedback);
  void result_callback(const GoalHandleFibonacci::WrappedResult& result);
};  // class FibonacciActionClient

}  // namespace uwb_waypoint_client
