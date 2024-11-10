#include "main_menu.hpp"

#include "../../core/game.hpp"

namespace game {

void MainMenu::show() {
    const auto tray = core::Game::trayManager();

    tray->showCursor();

    widgets.insert(widgets.end(), {
        tray->createButton(OgreBites::TL_CENTER,"MissionButton","Missions"),
        tray->createButton(OgreBites::TL_CENTER,"LanButton","LAN"),
        tray->createButton(OgreBites::TL_CENTER,"SettingsButton","Settings"),
        tray->createButton(OgreBites::TL_CENTER,"ExitButton","Exit")
    });
}

void MainMenu::hide() {
    for(auto& widget: widgets) {
        core::Game::trayManager()->destroyWidget(widget);
    }

    widgets.clear();
}

void MainMenu::buttonHit(OgreBites::Button* button)
{
    if (button->getName() == "MissionButton") {

    }
    else if (button->getName() == "LanButton") {
        core::Game::UIManager()->showOnly("LAN_MENU");
    }
    else if (button->getName() == "SettingsButton")
    {

    }
    else if (button->getName() == "ExitButton")
    {
        core::Game::root()->queueEndRendering();
    }
}

} // end namespace game

