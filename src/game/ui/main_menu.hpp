#pragma once

#include <OgreTrays.h>
#include <vector>

#include "../../core/ui_manager.hpp"

namespace game {

class UIManager;

class MainMenu: public core::UIListener
{
public:
    std::string getName() override { return "MAIN_MENU"; }

    void show() override;

    void hide() override;

    void buttonHit(OgreBites::Button* button) override;

protected:
    std::vector<OgreBites::Widget*> widgets;
};

} // end namespace game