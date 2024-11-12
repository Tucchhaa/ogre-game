#pragma once

#include "../core/game.hpp"

namespace game {

class UIManager;
class MenuScene;
class DemoScene;

class GalacticWarsGame : public core::Game {
public:
    GalacticWarsGame() { _instance.reset(this); }

    static GalacticWarsGame& instance() { return *_instance; }

    void init() override;

    static std::shared_ptr<game::UIManager> UIManager() { return instance().m_UIManager; }

    void startMenuScene();
    void startDemoScene();
    void startDemoSceneMultiplayer();

private:
    static std::shared_ptr<GalacticWarsGame> _instance;
    std::shared_ptr<game::UIManager> m_UIManager;

    std::shared_ptr<MenuScene> m_menuScene;
    std::shared_ptr<DemoScene> m_demoScene;
};

} // end namespace core