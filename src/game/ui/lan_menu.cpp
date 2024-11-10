#include "lan_menu.hpp"

#include "../../core/game.hpp"

namespace game {

void LANMenu::show() {
    const auto tray = core::Game::trayManager();
    tray->showCursor();

    tray->createButton(OgreBites::TL_CENTER,"open_peer_menu","Peer");
    tray->createButton(OgreBites::TL_CENTER,"open_host_menu","Host");
    tray->createButton(OgreBites::TL_BOTTOMLEFT,"return_to_main_menu","Return");
}

void LANMenu::buttonHit(OgreBites::Button* button) {
    if (button->getName() == "open_peer_menu") {
        core::Game::UIManager()->showOnly("LAN_CLIENT_MENU");
    }
    else if (button->getName() == "open_host_menu") {

    }
    else if (button->getName() == "return_to_main_menu") {
        core::Game::UIManager()->showOnly("MAIN_MENU");
    }
}

} // end namespace game