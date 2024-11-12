#include "lan_host_menu.hpp"

#include "../galactic_wars_game.hpp"
#include "../../core/game.hpp"
#include "../../core/network/server.hpp"

namespace game {

void LANHostMenu::show() {
    m_network->initServer();
    m_network->server()->start();

    m_tray->showCursor();

    m_countBox = m_tray->createTextBox(
        OgreBites::TL_CENTER,
        "connected_peers_num", getCountBoxText(),
        300, 50
    );

    m_callbackId = m_network->server()->onClientsChange.subscribe(this, &LANHostMenu::updateCountBox);

    m_tray->createButton(OgreBites::TL_CENTER,"start_lan_game","Start");

    m_tray->createButton(OgreBites::TL_BOTTOMLEFT,"return_to_lan_menu_from_host","Return");
}

void LANHostMenu::buttonHit(OgreBites::Button* button) {
    auto buttonName = button->getName();

    if(buttonName == "start_lan_game") {
        GalacticWarsGame::instance().startDemoSceneMultiplayer();
        m_network->server()->startGame();
        hide();
    }
    else if(buttonName == "return_to_lan_menu_from_host") {
        m_network->server()->onClientsChange.unsubscribe(m_callbackId);
        m_network->stop();
        m_ui->showOnly("LAN_MENU");
    }
}

void LANHostMenu::updateCountBox() const {
    m_countBox->setText(getCountBoxText());
}

std::string LANHostMenu::getCountBoxText() const {
    return "Connected players: " + std::to_string(m_network->server()->getClientsCount());
}

} // end namespace game

