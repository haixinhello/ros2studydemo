#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/msg/student.hpp"

using base_interfaces_demo::msg::Student;
using namespace std::chrono_literals;

class TalkerStu: public rclcpp::Node
{
public:
  TalkerStu():Node("talker_node_stu")
  {
    publisher_=this->create_publisher<Student>("chatter_stu",10);
    timer_=this->create_wall_timer(500ms,std::bind(&TalkerStu::on_timer,this));
  }

private:
  void on_timer()
  {
    auto stu=Student();
    stu.name="huluwa";
    stu.age=8;
    stu.height=2.20;

    publisher_->publish(stu);
    RCLCPP_INFO(this->get_logger(),"发布的消息：(%s,%d,%.2f)",stu.name.c_str(),stu.age,stu.height);

  }

  rclcpp::Publisher<Student>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;

};

int main(int argc, char ** argv)
{
  //初始化ROS2客户端
  rclcpp::init(argc,argv);
  //调用spin函数，传入自定义类对象指针
  rclcpp::spin(std::make_shared<TalkerStu>());
  //释放资源
  rclcpp::shutdown();

  return 0;
}
