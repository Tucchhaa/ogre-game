#pragma once

#include "core/game.hpp"

namespace game {

class UIManager;
class MenuScene;
class DemoScene;

enum class CollisionLayer {
    Default = 1<<0,
    StarFighter = 1<<1,
    StarShip = 1<<2,
    Asteroid = 1<<3,
    Bullet = 1<<4,
    All = 0x0FFFFFFF
};

class GalacticWarsGame : public core::Game {
public:
    GalacticWarsGame() { _instance.reset(this); }

    static GalacticWarsGame& instance() { return *_instance; }

    void init() override;

    static std::shared_ptr<game::UIManager> UIManager() { return instance().m_UIManager; }

    void startMenuScene();
    void startDemoScene();
    void startDemoSceneMultiplayer();

    void startSpaceScene();

private:
    static std::shared_ptr<GalacticWarsGame> _instance;
    std::shared_ptr<game::UIManager> m_UIManager;
};

} // end namespace core