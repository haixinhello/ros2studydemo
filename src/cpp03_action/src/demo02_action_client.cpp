#include "rclcpp/rclcpp.hpp"


class ProgressActionClient: public rclcpp::Node
{
public:
    ProgressActionClient():Node("progress_action_client_node_cpp")
    {
        RCLCPP_INFO(this->get_logger(),"action 客户端创建！");
    }
};


int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<ProgressActionClient>());
    rclcpp::shutdown();
    return 0;
}