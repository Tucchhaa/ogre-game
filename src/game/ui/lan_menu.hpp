#pragma once

#include "../../core/ui_manager.hpp"

namespace game {

class LANMenu : public core::UserInterface
{
public:
    std::string getName() override { return "LAN_MENU"; }

    void show() override;

    void buttonHit(OgreBites::Button* button) override;
};

}