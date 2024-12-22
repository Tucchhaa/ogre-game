#pragma once
#include <memory>

#include "core/scene/scene.hpp"
#include "game/objects/starship.hpp"

namespace game {
class Environment;
class Fighter;

class SpaceScene : public core::Scene {
public:
    SpaceScene();

    void init() override;

    void start() override;

    void update(float dt) override;

    void fixedUpdate(float dt) override;

private:
    std::shared_ptr<Environment> m_environment;
    std::shared_ptr<Fighter> m_fighter;
    std::shared_ptr<Starship> m_blueShip;
    std::shared_ptr<Starship> m_redShip;
    core::CustomSceneNode* m_earth = nullptr;
    Ogre::Vector3 m_earthDelta;
};

} // end namespace game
