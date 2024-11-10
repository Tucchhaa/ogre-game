#include "galactic_wars_game.hpp"

#include "../core/ui_manager.hpp"
#include "ui/main_menu.hpp"
#include "ui/lan_menu.hpp"

namespace game {

std::shared_ptr<GalacticWarsGame> GalacticWarsGame::_instance = nullptr;

void GalacticWarsGame::init() {
    Game::init();

    Game::UIManager()->addListener(std::make_shared<MainMenu>());
    Game::UIManager()->addListener(std::make_shared<LANMenu>());

    Game::UIManager()->showOnly("MAIN_MENU");
}

}
