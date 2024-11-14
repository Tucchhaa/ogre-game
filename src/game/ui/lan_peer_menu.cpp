#include "lan_peer_menu.hpp"

#include "../galactic_wars_game.hpp"
#include "../../core/game.hpp"
#include "../../core/network/client.hpp"
#include "../../core/utils.hpp"

using namespace std;

namespace game {

void LANPeerMenu::show() {
    m_tray->showCursor();

    m_tray->createButton(OgreBites::TL_CENTER, "search_lan_games", "Search");

    auto servers = m_network->getLANServers();

    if(servers.empty()) {
        auto a =m_tray->createTextBox(OgreBites::TL_CENTER, "empty_text", "", 300, 100);
        a->appendText("No servers found");
    }
    else {
        for (size_t i = 0; i < servers.size(); i++) {
            auto server = servers[i];
            string text = core::utils::convertIP(server.host) + ':' + to_string(server.port);
            string labelName = "connect_btn_label_" + to_string(i);
            string buttonName = "connect_to_lan_" + to_string(i);

            m_tray->createLabel(OgreBites::TL_CENTER, labelName, text);
            m_tray->createButton(OgreBites::TL_CENTER, buttonName, "Connect");
        }
    }

    m_tray->createButton(OgreBites::TL_BOTTOMLEFT,"return_to_lan_menu_from_peer","Return");
}

void LANPeerMenu::buttonHit(OgreBites::Button* button) {
    const auto& buttonName = button->getName();
    
    if(buttonName == "search_lan_games") {
        m_network->searchLANServers();
        update();
    }
    else if(buttonName.find("connect_to_lan_") != string::npos) {
        const auto index_str = buttonName.substr(buttonName.rfind('_') + 1);
        const int index = stoi(index_str);
        const auto& server = m_network->getLANServers()[index];

        m_network->initClient();
        // TODO: handle case if connect was failed
        m_network->client()->connect(server);
        GalacticWarsGame::instance().startDemoSceneMultiplayer();
        m_network->client()->start();
        hide();
    }
    else if (buttonName == "return_to_lan_menu_from_peer") {
        core::Game::UIManager()->showOnly("LAN_MENU");
    }
}

} // end namespace game
