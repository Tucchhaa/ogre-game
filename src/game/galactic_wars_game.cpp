#include "galactic_wars_game.hpp"

#include "../core/ui_manager.hpp"
#include "ui/lan_peer_menu.hpp"
#include "ui/main_menu.hpp"
#include "ui/lan_menu.hpp"

#include "scenes/menu_scene.hpp"
#include "scenes/demo_scene.hpp"

namespace game {

std::shared_ptr<GalacticWarsGame> GalacticWarsGame::_instance = nullptr;

void GalacticWarsGame::init() {
    Game::init();

    Game::UIManager()->addListener(std::make_shared<MainMenu>());
    Game::UIManager()->addListener(std::make_shared<LANMenu>());
    Game::UIManager()->addListener(std::make_shared<LANPeerMenu>());

    m_menuScene = std::make_shared<MenuScene>();
    m_demoScene = std::make_shared<DemoScene>();
}

void GalacticWarsGame::startMenuScene() {
    setScene(m_menuScene);
}

void GalacticWarsGame::startDemoScene() {
    setScene(m_demoScene);
}

}
