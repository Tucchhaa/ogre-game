#include "scene.hpp"

#include "game.hpp"

void Scene::init() {
    m_sceneManager = Game::sceneManager();
    m_rootNode = m_sceneManager->getRootSceneNode();
}
