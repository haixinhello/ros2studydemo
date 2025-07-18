#include "rclcpp/rclcpp.hpp"


class ParamServer: public rclcpp::Node
{
public:
    ParamServer():Node("param_server_node_cpp")
    {
        RCLCPP_INFO(this->get_logger(),"参数服务端创建了！");
        
    }
};


int main(int argc, char const *argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<ParamServer>());
    rclcpp::shutdown();
    return 0;
}