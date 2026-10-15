#pragma once
#include "app/robot_config.hpp"

class RobotEthernet
{
private:
    uint8_t socket_teleop_ = 0;

public:
    bool init();
    bool send_teleop(const robot_config::teleop_t& data);
};
