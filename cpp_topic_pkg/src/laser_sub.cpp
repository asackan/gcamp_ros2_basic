// Copyright 2021 Seoul Business Agency Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// [http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

using LaserScan = sensor_msgs::msg::LaserScan;

class LaserSub : public rclcpp::Node {
private:
  rclcpp::Subscription<LaserScan>::SharedPtr m_sub;

public:
  LaserSub() : Node("topic_sub_oop_node") {
    m_sub = this->create_subscription<LaserScan>(
        "skidbot/scan", 10,
        [this](const LaserScan::SharedPtr msg){sub_callback(msg);} );
  }

  void sub_callback(const LaserScan::SharedPtr msg) {
    // std::cout << (msg->ranges).size() << std::endl;

    // for (auto e : msg->ranges)
    //   std::cout << e << std::endl;

    RCLCPP_INFO(this->get_logger(), "Distance from Front Object : %f", (msg->ranges)[360]);
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LaserSub>());
  rclcpp::shutdown();

  return 0;
}
