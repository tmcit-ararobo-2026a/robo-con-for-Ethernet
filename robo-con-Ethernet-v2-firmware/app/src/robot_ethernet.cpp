#include "app/robot_ethernet.hpp"

#include <cstdio>
#include <cstring>

#include "gpio.h"
#include "wiznet_ether/socket.hpp"
#include "wiznet_ether/w5500_spi.hpp"

bool RobotEthernet::init()
{
    // ハードウェア初期化
    if (W5500Init()) {
    } else {
        // 失敗したらW5500が利用できない
        return false;
    }
    uint8_t ver = getVERSIONR();  // または WIZCHIP_READ(VERSIONR);
    printf("W5500 Version: 0x%02X\n", ver);

    // ネットワーク情報の設定
    wiz_NetInfo_t net_info = {
        .mac = {0x48, 0x44, 0x25, 0xA3, 0x81, 0xF2},

        .ip =
            {robot_config::ip::teleop[0],
                robot_config::ip::teleop[1],
                robot_config::ip::teleop[2],
                robot_config::ip::teleop[3]},

        .sn = {255, 255, 255, 0},

        .gw =
            {robot_config::ip::pc_wifi[0],
                robot_config::ip::pc_wifi[1],
                robot_config::ip::pc_wifi[2],
                robot_config::ip::pc_wifi[3]}, // ロボット内部LANのゲートウェイはPC

        .dns = {0, 0, 0, 0},

        .dhcp = NETINFO_STATIC
    };

    wizchip_setnetinfo(&net_info);

    // ネットワーク情報の確認
    wiz_NetInfo tmpNetInfo;
    wizchip_getnetinfo(&tmpNetInfo);
    printf(
        "MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
        tmpNetInfo.mac[0],
        tmpNetInfo.mac[1],
        tmpNetInfo.mac[2],
        tmpNetInfo.mac[3],
        tmpNetInfo.mac[4],
        tmpNetInfo.mac[5]
    );
    printf(
        "IP: %d.%d.%d.%d\n", tmpNetInfo.ip[0], tmpNetInfo.ip[1], tmpNetInfo.ip[2], tmpNetInfo.ip[3]
    );

    // 通信レイテンシ向上のため再送信回数を1回、タイムアウトを100msに設定
    setRCR(1);
    setRTR(100);

    // ソケット作成
    socket(socket_teleop_, Sn_MR_UDP, robot_config::port::teleop, SF_IO_NONBLOCK);

    return true;
}

bool RobotEthernet::send_teleop(const robot_config::teleop_t& data)
{
    robot_config::teleop_u tx_data;
    tx_data.value        = data;
    tx_data.value.header = robot_config::header::teleop;

    uint8_t ip_address[4];
    memcpy(ip_address, robot_config::ip::mainboard, 4);

    int32_t len = sendto(
        socket_teleop_, tx_data.binary, sizeof(tx_data), ip_address, robot_config::port::teleop
    );

    if (len != sizeof(robot_config::feedback_u)) return false;
    return true;
}