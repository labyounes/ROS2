cmake_minimum_required(VERSION 3.8)
project(ros2_person_exchange)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# Generate the custom message
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/PersonInfo.msg"
)

ament_export_dependencies(rosidl_default_runtime)

# Get the generated type support target
rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

# Talker node
add_executable(person_talker src/person_talker.cpp)
ament_target_dependencies(person_talker rclcpp)
target_link_libraries(person_talker "${cpp_typesupport_target}")

# Listener node
add_executable(person_listener src/person_listener.cpp)
ament_target_dependencies(person_listener rclcpp)
target_link_libraries(person_listener "${cpp_typesupport_target}")

install(TARGETS
  person_talker
  person_listener
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
