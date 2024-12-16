#include "galactic_wars_game.hpp"

#include "core/ui_manager.hpp"
#include "core/network/server.hpp"

#include "ui/main_menu.hpp"
#include "ui/lan_menu.hpp"
#include "ui/lan_peer_menu.hpp"
#include "ui/lan_host_menu.hpp"

#include "scenes/menu_scene.hpp"
#include "scenes/demo_scene.hpp"
#include "scenes/space_scene/scene.hpp"

#include "objects/star_fighter_controller.hpp"

namespace game {

std::shared_ptr<GalacticWarsGame> GalacticWarsGame::_instance = nullptr;

void GalacticWarsGame::init() {
    Game::init();

    root()->addMovableObjectFactory(new StarFighterControllerFactory);

    Game::UIManager()->addListener(std::make_shared<MainMenu>());
    Game::UIManager()->addListener(std::make_shared<LANMenu>());
    Game::UIManager()->addListener(std::make_shared<LANPeerMenu>());
    Game::UIManager()->addListener(std::make_shared<LANHostMenu>());
}

void GalacticWarsGame::startMenuScene() {
    const auto scene = std::make_shared<MenuScene>();
    setScene(scene);
}

void GalacticWarsGame::startDemoScene() {
    const auto scene = std::make_shared<DemoScene>();
    const auto singlePlayer = std::make_shared<core::SinglePlayer>();
    setGameLoopThread(singlePlayer);

    setScene(scene);
}

void GalacticWarsGame::startDemoSceneMultiplayer() {
    const auto scene = std::make_shared<DemoScene>();
    setScene(scene);
}

void GalacticWarsGame::startSpaceScene() {
    const auto scene = std::make_shared<SpaceScene>();
    const auto singlePlayer = std::make_shared<core::SinglePlayer>();
    setGameLoopThread(singlePlayer);

    setScene(scene);
}

}
