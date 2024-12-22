#include "scene.hpp"

#include "environment.hpp"
#include "core/input.hpp"
#include "core/window_manager.hpp"
#include "core/objects/transform.hpp"
#include "game/objects/star_fighters/fighter.hpp"
#include "game/ui/fighter_indicators.hpp"

/*
TODO:
Graphics:
- Precompute tangents
- Ambient occlusion map
- Bloom effect
- Particles

Game:
- Correct rotation on Right-Click in star fighter controller
- GameLoop
- Health
- Shooting
- Reviving
- Enemy AI
- Turret AI
- Game UI
- Death zone
 */

namespace game {

SpaceScene::SpaceScene() {
    m_environment = std::make_shared<Environment>(this);
}

void SpaceScene::init() {
    Scene::init();

    m_physics->dynamicsWorld()->setGravity(btVector3(0, 0, 0));

    m_sceneManager->setSkyBox(true, "Skybox/Starfield", 10000, true);

    auto* cameraNode = m_environment->createCamera();
    auto* lightNode = m_environment->createLight();
    auto* asteroidsNode = m_environment->createAsteroids();
    m_earth = m_environment->createEarth();

    m_rootNode->addChild(cameraNode);
    m_rootNode->addChild(lightNode);
    m_rootNode->addChild(m_earth);
    m_rootNode->addChild(asteroidsNode);

    mainCamera = static_cast<Ogre::Camera*>(cameraNode->getAttachedObject("MainCamera"));

    m_fighter = m_environment->createStarFighter();
    m_blueShip = m_environment->createBlueStarship();
    m_redShip = m_environment->createRedStarship();

    m_earthDelta = m_earth->getPosition() - m_fighter->node()->getPosition();
}

void SpaceScene::start() {
    Scene::start();

    m_fighter->indicators()->show();
}

void SpaceScene::update(float dt) {
    Scene::update(dt);

    if(core::Game::input()->isKeyDown(core::Key::ESCAPE)) {
        core::Game::instance().stop();
    }

    if(core::Game::input()->isKeyDown(core::Key::SPACE)) {
        core::Game::windowManager()->relativeMouseEnabled(
            !core::Game::windowManager()->relativeMouseEnabled()
        );
    }

    m_earth->setPosition(m_fighter->node()->getPosition() + m_earthDelta);
    m_earth->transform()->resetState();
}

void SpaceScene::fixedUpdate(float dt) {

}

} // end namespace game