#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>

#include "action_tutorials_interfaces/action/fibonacci.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "uwb_waypoint_action_client/uwb_waypoint_client.hpp"

namespace uwb_waypoint_client {

FibonacciActionClient::FibonacciActionClient()
    : Node("fibonacci_action_client") {
  this->client_ptr_ =
      rclcpp_action::create_client<Fibonacci>(this, "fibonacci");
  motion_cmd_subscription_ =
      this->create_subscription<geometry_msgs::msg::Twist>(
          "/cmd_vel", 5,
          std::bind(&FibonacciActionClient::TwistCmdCallback, this,
                    std::placeholders::_1));
  // this->timer_ = this->create_wall_timer(
  //     std::chrono::milliseconds(500),
  //     std::bind(&FibonacciActionClient::send_goal, this));
}
void FibonacciActionClient::TwistCmdCallback(
    const geometry_msgs::msg::Twist::SharedPtr msg) {
  RCLCPP_INFO(this->get_logger(), "twist callback");
  int fibo_order = 10 + int(msg->linear.x * 10);
  RCLCPP_INFO(this->get_logger(),
              "PUBLISHING ODOM, dt: " + std::to_string(fibo_order));
  send_goal(fibo_order);
}
void FibonacciActionClient::send_goal(int fibo_order) {
  using namespace std::placeholders;
  RCLCPP_INFO(this->get_logger(), "test 1");


  RCLCPP_INFO(this->get_logger(), "test 2");
  if (!this->client_ptr_->wait_for_action_server()) {
    RCLCPP_ERROR(this->get_logger(),
                 "Action server not available after waiting");
    rclcpp::shutdown();
  }
  RCLCPP_INFO(this->get_logger(), "test 3");

  auto goal_msg = Fibonacci::Goal();
  RCLCPP_INFO(this->get_logger(), "test 4");
  goal_msg.order = fibo_order;

  RCLCPP_INFO(this->get_logger(), "Sending goal");

  auto send_goal_options = rclcpp_action::Client<Fibonacci>::SendGoalOptions();
  send_goal_options.goal_response_callback =
      std::bind(&FibonacciActionClient::goal_response_callback, this, _1);
  send_goal_options.feedback_callback =
      std::bind(&FibonacciActionClient::feedback_callback, this, _1, _2);
  send_goal_options.result_callback =
      std::bind(&FibonacciActionClient::result_callback, this, _1);
  this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
}

void FibonacciActionClient::goal_response_callback(
    std::shared_future<GoalHandleFibonacci::SharedPtr> future) {
  auto goal_handle = future.get();
  if (!goal_handle) {
    RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
  } else {
    RCLCPP_INFO(this->get_logger(),
                "Goal accepted by server, waiting for result");
  }
}

void FibonacciActionClient::feedback_callback(
    GoalHandleFibonacci::SharedPtr,
    const std::shared_ptr<const Fibonacci::Feedback> feedback) {
  std::stringstream ss;
  ss << "Next number in sequence received: ";
  for (auto number : feedback->partial_sequence) {
    ss << number << " ";
  }
  RCLCPP_INFO(this->get_logger(), ss.str().c_str());
}

void FibonacciActionClient::result_callback(
    const GoalHandleFibonacci::WrappedResult& result) {
  switch (result.code) {
    case rclcpp_action::ResultCode::SUCCEEDED:
      break;
    case rclcpp_action::ResultCode::ABORTED:
      RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
      return;
    case rclcpp_action::ResultCode::CANCELED:
      RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
      return;
    default:
      RCLCPP_ERROR(this->get_logger(), "Unknown result code");
      return;
  }
  std::stringstream ss;
  ss << "Result received: ";
  for (auto number : result.result->sequence) {
    ss << number << " ";
  }
  RCLCPP_INFO(this->get_logger(), ss.str().c_str());
  rclcpp::shutdown();
}

}  // namespace uwb_waypoint_client

// RCLCPP_COMPONENTS_REGISTER_NODE(uwb_waypoint_client::FibonacciActionClient)
