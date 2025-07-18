#include "rclcpp/rclcpp.hpp"


class ParamClient: public rclcpp::Node
{
public:
    ParamClient():Node("param_client_node_cpp")
    {
        RCLCPP_INFO(this->get_logger(),"参数客户端创建了！");
    }
};


int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<ParamClient>());
    rclcpp::shutdown();
    return 0;
}