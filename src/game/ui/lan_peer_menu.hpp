#pragma once

#include "../../core/ui_manager.hpp"

namespace game {

class LANPeerMenu : public core::UIListener {
    std::string getName() override { return "LAN_CLIENT_MENU"; }

    void show() override;

    void buttonHit(OgreBites::Button* button) override;
};

} // end namespace game