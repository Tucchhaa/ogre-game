#include "scene.hpp"

#include "game.hpp"
#include "physics_world.hpp"

namespace core {

void Scene::init() {
    m_sceneManager = Game::sceneManager();
    m_rootNode = static_cast<CustomSceneNode*>(m_sceneManager->getRootSceneNode());
}

void Scene::update(float dt) {
    if(Game::debugMode()) {
        Game::physics()->drawColliders();
    }
}

} // end namespace core