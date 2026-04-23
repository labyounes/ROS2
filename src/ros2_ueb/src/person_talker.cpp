#include "rclcpp/rclcpp.hpp"
#include "ros2_person_exchange/msg/person_info.hpp"

class PersonTalker : public rclcpp::Node
{
public:
  PersonTalker() : Node("person_talker")
  {
    // Declare parameters with defaults
    this->declare_parameter("firstname", "Younes");
    this->declare_parameter("surname", "Labidi");
    this->declare_parameter("age", NULL);
    this->declare_parameter("bachelor_course", "Project Engineering");
    this->declare_parameter("publish_period_ms", 1000);

    publisher_ = this->create_publisher<ros2_person_exchange::msg::PersonInfo>(
      "person_info", 10);

    int period_ms = this->get_parameter("publish_period_ms").as_int();
    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(period_ms),
      std::bind(&PersonTalker::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto msg = ros2_person_exchange::msg::PersonInfo();
    msg.firstname       = this->get_parameter("firstname").as_string();
    msg.surname         = this->get_parameter("surname").as_string();
    msg.age             = this->get_parameter("age").as_int();
    msg.bachelor_course = this->get_parameter("bachelor_course").as_string();

    RCLCPP_INFO(this->get_logger(), "Publishing: %s %s, age %d, course: %s",
      msg.firstname.c_str(), msg.surname.c_str(),
      msg.age, msg.bachelor_course.c_str());

    publisher_->publish(msg);
  }

  rclcpp::Publisher<ros2_person_exchange::msg::PersonInfo>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PersonTalker>());
  rclcpp::shutdown();
  return 0;
}