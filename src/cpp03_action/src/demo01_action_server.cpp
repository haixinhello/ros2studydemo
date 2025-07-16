#include "rclcpp/rclcpp.hpp"


class ProgressActionServer: public rclcpp::Node
{
public:
  ProgressActionServer():Node("progress_action_server_node_cpp")
  {
    RCLCPP_INFO(this->get_logger(),"action 服务端创建！");
  }
};


int main(int argc, char const *argv[])
{
  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<ProgressActionServer>());
  rclcpp::shutdown();
  return 0;
}
