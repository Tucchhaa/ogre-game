#include "scene.hpp"

#include <Overlay/OgreOverlaySystem.h>

#include "../game.hpp"
#include "../physics/physics_world.hpp"

namespace core {

Scene::Scene() {
    m_sceneManager = static_cast<CustomSceneManager*>(Game::root()->createSceneManager(CUSTOM_SCENE_MANAGER_TYPE));
    m_rootNode = static_cast<CustomSceneNode*>(m_sceneManager->getRootSceneNode());

    Game::shaderGenerator()->addSceneManager(m_sceneManager);
    m_sceneManager->addRenderQueueListener(Game::appContext()->getOverlaySystem());
}

void Scene::init() {
    m_physics = std::make_unique<PhysicsWorld>();
}

void Scene::start() {
    m_sceneManager->_updateSceneGraph(mainCamera);
}

void Scene::stop() {
    m_sceneManager->clearScene();
    m_physics.reset();
    Game::shaderGenerator()->removeSceneManager(m_sceneManager);
    Game::root()->destroySceneManager(m_sceneManager);
}

void Scene::update(float dt) {
    if(Game::debugMode()) {
        Game::physics()->drawColliders();
    }
}

} // end namespace core