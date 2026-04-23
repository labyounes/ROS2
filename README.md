# ROS2 Person Exchange (Talker & Listener)

This project is a simple ROS2 example package that demonstrates basic publisher/subscriber communication using two nodes:

- **Person Talker** → publishes a person message periodically
- **Person Listener** → subscribes and prints received messages

The project is implemented in **C++ using ROS2 (Jazzy)**.

---

## 📦 Package Structure


ros2_ueb/
├── src/
│ ├── person_talker.cpp
│ └── person_listener.cpp
├── CMakeLists.txt
├── package.xml
