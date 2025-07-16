#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/srv/add_ints.hpp"

using base_interfaces_demo::srv::AddInts;
using namespace std::chrono_literals;

class AddIntsClient: public rclcpp::Node
{
public:
    AddIntsClient():Node("add_ints_client_node_cpp")
    {
        RCLCPP_INFO(this->get_logger(),"客户端创建！");
        client_=this->create_client<AddInts>("add_ints");
    }

    bool connect_server()
    {
        while(!client_->wait_for_service(2s))
        {
            if (!rclcpp::ok())
            {
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"强行终止客户端！");
                return false;
            }
            
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"服务器连接中...");

        }

        return true;
    }

    rclcpp::Client<AddInts>::FutureAndRequestId send_request(int num1,int num2)
    {
        auto request =std::make_shared<AddInts::Request>();
        request->num1=num1;
        request->num2=num2;
        return client_->async_send_request(request);
    }

private:
    rclcpp::Client<AddInts>::SharedPtr client_;

};


int main(int argc, char const *argv[])
{
    if(argc !=3)
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"请提交两个整型数字！");
        return 1;
    }
    rclcpp::init(argc,argv);
    auto client=std::make_shared<AddIntsClient>();
    bool flag=client->connect_server();
    if (!flag)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"服务器连接失败，程序退出！");
        return 0;
    }

    auto future=client->send_request(atoi(argv[1]),atoi(argv[2]));
    if (rclcpp::spin_until_future_complete(client,future)==rclcpp::FutureReturnCode::SUCCESS) 
    {
        RCLCPP_INFO(client->get_logger(),"响应成功！sum=%d",future.get()->sum);
    }
    else
    {
        RCLCPP_INFO(client->get_logger(),"响应失败！");
    }
    
    rclcpp::shutdown();
    return 0;
}