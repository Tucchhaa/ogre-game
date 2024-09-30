#include "scene.hpp"

#include "game.hpp"

namespace core {

void Scene::init() {
    m_sceneManager = Game::sceneManager();
    m_rootNode = m_sceneManager->getRootSceneNode();
}

bool Scene::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    Game::physics()->stepSimulation(evt.timeSinceLastFrame);

    if(Game::debugMode()) {
        Game::physics()->drawColliders();
    }

    return true;
}

} // end namespace core