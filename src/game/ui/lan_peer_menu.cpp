#include "lan_peer_menu.hpp"

#include "../../core/game.hpp"

namespace game {

void LANPeerMenu::show() {
    const auto tray = core::Game::trayManager();
    tray->showCursor();

    std::vector<std::string> host_list = {
        "192.168.0.1",
        "192.168.1.1",
        "10.0.0.1",
        "10.0.1.1",
        "172.16.0.1",
        "172.16.1.1",
        "8.8.8.8",
        "8.8.4.4",
        "1.1.1.1",
        "1.0.0.1"
    };

    for (size_t i = 0; i < host_list.size(); ++i) {
        std::string line = host_list[i];
        std::string labelName = "LineLabel" + std::to_string(i);
        std::string buttonName = "LineButton" + std::to_string(i);

        tray->createLabel(OgreBites::TL_CENTER, labelName, line, 300);
        tray->createButton(OgreBites::TL_CENTER, buttonName, "Action " + std::to_string(i + 1), 100);
    }

    tray->createButton(OgreBites::TL_BOTTOMLEFT,"return_to_lan_menu","Return");
}

void LANPeerMenu::buttonHit(OgreBites::Button* button) {
    if (button->getName() == "return_to_lan_menu") {
        core::Game::UIManager()->showOnly("LAN_MENU");
    }
}

} // end namespace game
