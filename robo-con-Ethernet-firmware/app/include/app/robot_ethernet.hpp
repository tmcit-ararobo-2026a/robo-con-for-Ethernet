#pragma once
#include "app/robot_config.hpp"

class RobotEthernet
{
private:
    uint8_t socket_cmd_    = 0;
    uint8_t socket_teleop_ = 1;
    uint8_t socket_debug_  = 2;

public:
    bool init();
    bool send_teleop(const robot_config::teleop_t& data);
};
