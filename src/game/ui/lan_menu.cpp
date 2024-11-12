#include "lan_menu.hpp"

#include "../../core/game.hpp"
#include "../../core/network/server.hpp"

namespace game {

void LANMenu::show() {
    m_tray->showCursor();

    m_tray->createButton(OgreBites::TL_CENTER,"open_peer_menu","Peer");
    m_tray->createButton(OgreBites::TL_CENTER,"open_host_menu","Host");
    m_tray->createButton(OgreBites::TL_BOTTOMLEFT,"return_to_main_menu","Return");
}

void LANMenu::buttonHit(OgreBites::Button* button) {
    auto buttonName = button->getName();

    if (buttonName == "open_peer_menu") {
        m_ui->showOnly("LAN_PEER_MENU");
    }
    else if (buttonName == "open_host_menu") {
        m_ui->showOnly("LAN_HOST_MENU");
    }
    else if (buttonName == "return_to_main_menu") {
        m_ui->showOnly("MAIN_MENU");
    }
}

} // end namespace game