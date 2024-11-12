#include "lan_peer_menu.hpp"

#include "../galactic_wars_game.hpp"
#include "../../core/game.hpp"
#include "../../core/network/client.hpp"

using namespace std;

namespace game {

void LANPeerMenu::show() {
    m_tray->showCursor();

    m_tray->createButton(OgreBites::TL_CENTER, "search_lan_games", "Search");

    auto servers = m_network->getLANServers();

    if(servers.empty()) {
        m_tray->createTextBox(OgreBites::TL_CENTER, "empty_text", "No servers found", 300, 50);
    }
    else {
        for (size_t i = 0; i < servers.size(); i++) {
            auto server = servers[i];
            string text = to_string(server.host) + ':' + to_string(server.port);
            string labelName = "LineLabel" + to_string(i);
            string buttonName = "connect_to_lan_" + to_string(i);

            m_tray->createLabel(OgreBites::TL_CENTER, labelName, text);
            m_tray->createButton(OgreBites::TL_CENTER, "connect", "Connect");
        }
    }

    m_tray->createButton(OgreBites::TL_BOTTOMLEFT,"return_to_lan_menu_from_peer","Return");
}

void LANPeerMenu::buttonHit(OgreBites::Button* button) {
    auto buttonName = button->getName();
    
    if(buttonName == "search_lan_games") {
        // TODO: handle case when no servers found
        m_network->searchLANServers();
        hide();
        show(); // render menu again to apply changes
    }
    else if(buttonName == "connect") {
        m_network->initClient();
        // TODO: make it to connect to the selected server, not the the first server
        // TODO: handle case if connect was failed
        m_network->client()->connect(
            m_network->getLANServers()[0]
        );
        GalacticWarsGame::instance().startDemoSceneMultiplayer();
        m_network->client()->start();
        hide();
    }
    else if (buttonName == "return_to_lan_menu_from_peer") {
        core::Game::UIManager()->showOnly("LAN_MENU");
    }
}

} // end namespace game
