

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class Talker: public rclcpp::Node
{
  public:
  Talker():Node("talker_node_cpp"),count(0)
  {
    RCLCPP_INFO(this->get_logger(),"发布节点创建！");

    publisher_=this->create_publisher<std_msgs::msg::String>("chatter",10);

    timer_=this->create_wall_timer(1s,std::bind(&Talker::on_timer,this));

  }

  private:
  void on_timer()
  {
    auto message=std_msgs::msg::String();
    message.data="hello world"+std::to_string(count++);
    RCLCPP_INFO(this->get_logger(),"发布方发布的消息：%s",message.data.c_str());
    publisher_->publish(message);
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  size_t count;

};

int main(int argc, char ** argv)
{
  //初始化ROS2客户端
  rclcpp::init(argc,argv);
  //调用spin函数，传入自定义类对象指针
  rclcpp::spin(std::make_shared<Talker>());
  //释放资源
  rclcpp::shutdown();

  return 0;
}
