#include <set>
#include "rclcpp/rclcpp.hpp"
#include "ros2_person_exchange/msg/person_info.hpp"

struct PersonInfoEntry {
  std::string firstname;
  std::string surname;
  int32_t age;
  std::string bachelor_course;

  // Needed so std::set can order and deduplicate entries
  bool operator<(const PersonInfoEntry & other) const {
    if (firstname != other.firstname) return firstname < other.firstname;
    if (surname   != other.surname)   return surname   < other.surname;
    if (age       != other.age)       return age       < other.age;
    return bachelor_course < other.bachelor_course;
  }
};

class PersonListener : public rclcpp::Node
{
public:
  PersonListener() : Node("person_listener")
  {
    subscription_ = this->create_subscription<ros2_person_exchange::msg::PersonInfo>(
      "person_info", 10,
      std::bind(&PersonListener::listener_callback, this, std::placeholders::_1));
  }

private:
  void listener_callback(const ros2_person_exchange::msg::PersonInfo & msg)
  {
    PersonInfoEntry entry{msg.firstname, msg.surname, msg.age, msg.bachelor_course};
    received_entries_.insert(entry);  // duplicates are ignored automatically

    RCLCPP_INFO(this->get_logger(),
      "Summary of distinct received information (%zu):", received_entries_.size());

    int i = 1;
    for (const auto & e : received_entries_) {
      RCLCPP_INFO(this->get_logger(), "  %d. %s %s, age %d, Bachelor course: %s",
        i++, e.firstname.c_str(), e.surname.c_str(),
        e.age, e.bachelor_course.c_str());
    }
  }

  rclcpp::Subscription<ros2_person_exchange::msg::PersonInfo>::SharedPtr subscription_;
  std::set<PersonInfoEntry> received_entries_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PersonListener>());
  rclcpp::shutdown();
  return 0;
}