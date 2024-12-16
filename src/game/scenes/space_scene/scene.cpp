#include "scene.hpp"

#include "environment.hpp"
#include "core/input.hpp"
#include "core/window_manager.hpp"
#include "game/objects/star_fighters/fighter.hpp"
#include "game/ui/fighter_indicators.hpp"

game::SpaceScene::SpaceScene() {
    m_environment = std::make_shared<Environment>(this);
}

void game::SpaceScene::init() {
    Scene::init();

    m_physics->dynamicsWorld()->setGravity(btVector3(0, 0, 0));

    m_sceneManager->setSkyBox(true, "Skybox/Starfield", 10000, true);

    auto* cameraNode = m_environment->createCamera();
    auto* lightNode = m_environment->createLight();
    auto* earthNode = m_environment->createEarth();
    auto* starshipNode = m_environment->createStarship();
    auto* asteroidsNode = m_environment->createAsteroids();

    m_rootNode->addChild(cameraNode);
    m_rootNode->addChild(lightNode);
    m_rootNode->addChild(earthNode);
    m_rootNode->addChild(starshipNode);
    m_rootNode->addChild(asteroidsNode);

    mainCamera = static_cast<Ogre::Camera*>(cameraNode->getAttachedObject("MainCamera"));
    m_fighter = m_environment->createStarFighter();
}

void game::SpaceScene::start() {
    Scene::start();

    m_fighter->indicators()->show();
}

void game::SpaceScene::update(float dt) {
    Scene::update(dt);

    if(core::Game::input()->isKeyDown(core::Key::ESCAPE)) {
        core::Game::instance().stop();
    }

    if(core::Game::input()->isKeyDown(core::Key::SPACE)) {
        core::Game::windowManager()->relativeMouseEnabled(
            !core::Game::windowManager()->relativeMouseEnabled()
        );
    }
}
