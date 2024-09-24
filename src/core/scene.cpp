#include "scene.hpp"

#include "game.hpp"

namespace core {

void Scene::init() {
    m_sceneManager = Game::sceneManager();
    m_rootNode = m_sceneManager->getRootSceneNode();
}

} // end namespace core