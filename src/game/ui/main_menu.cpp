#include "main_menu.hpp"

#include "../galactic_wars_game.hpp"
#include "../../core/game.hpp"

namespace game {

void MainMenu::show() {
    const auto tray = core::Game::trayManager();

    tray->showCursor();

    tray->createButton(OgreBites::TL_CENTER,"open_missions_menu","Missions");
    tray->createButton(OgreBites::TL_CENTER,"open_lan_menu","LAN");
    tray->createButton(OgreBites::TL_CENTER,"open_settings_menu","Settings");
    tray->createButton(OgreBites::TL_CENTER,"exit","Exit");
}

void MainMenu::buttonHit(OgreBites::Button* button) {
    if (button->getName() == "open_missions_menu") {
        hide();
        core::Game::trayManager()->hideCursor();

        GalacticWarsGame::instance().startDemoScene();
    }
    else if (button->getName() == "open_lan_menu") {
        core::Game::UIManager()->showOnly("LAN_MENU");
    }
    else if (button->getName() == "open_settings_menu")
    {

    }
    else if (button->getName() == "exit")
    {
        core::Game::root()->queueEndRendering();
    }
}

} // end namespace game

