#pragma once

namespace core {
/**
 * Note: implement assignment of dynamic port
 */
constexpr int LAN_LISTEN_PORT = 8888;

const auto LAN_DISCOVER_MESSAGE = "DISCOVER_OGRE_GAME_LAN_SERVER\0";
const size_t LAN_DISCOVER_MESSAGE_LEN{strlen(LAN_DISCOVER_MESSAGE)};

const auto LAN_DISCOVERED_MESSAGE = "DISCOVERED_OGRE_GAME_LAN_SERVER\0";
const size_t LAN_DISCOVERED_MESSAGE_LEN{strlen(LAN_DISCOVERED_MESSAGE)};

}
