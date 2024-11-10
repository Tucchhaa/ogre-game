#include "galactic_wars_game.hpp"

#include "ui/ui_manager.hpp"

namespace game {

std::shared_ptr<GalacticWarsGame> GalacticWarsGame::_instance = nullptr;

void GalacticWarsGame::init() {
    Game::init();

    m_UIManager = std::make_shared<game::UIManager>();
}

}
