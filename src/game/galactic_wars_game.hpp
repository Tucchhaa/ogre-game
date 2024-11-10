#pragma once

#include "../core/game.hpp"

namespace game {

class UIManager;

class GalacticWarsGame : public core::Game {
public:
    GalacticWarsGame() { _instance.reset(this); }

    static GalacticWarsGame& instance() { return *_instance; }

    void init() override;

    static std::shared_ptr<game::UIManager> UIManager() { return instance().m_UIManager; }

private:
    static std::shared_ptr<GalacticWarsGame> _instance;
    std::shared_ptr<game::UIManager> m_UIManager;
};

} // end namespace core