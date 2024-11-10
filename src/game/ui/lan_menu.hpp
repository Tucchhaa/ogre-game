#pragma once

#include <OgreTrays.h>

#include "../../core/ui_manager.hpp"

namespace game {

class UIManager;

class LANMenu : public core::UIListener
{
public:
    std::string getName() override { return "LAN_MENU"; }

    void show() override;

    void hide() override;

    void buttonHit(OgreBites::Button* button) override;

    void createWidget(const std::vector<std::string>&);

protected:
    std::vector<OgreBites::Widget*> widgets;
    std::map<OgreBites::Button*, std::string> buttonLines;
};

}