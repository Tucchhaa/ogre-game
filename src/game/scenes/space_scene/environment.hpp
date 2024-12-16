#pragma once

#include <memory>

namespace Ogre {
class Camera;
class SceneNode;
}

namespace core {

class CustomSceneManager;
class CustomSceneNode;

}

namespace game {
class Fighter;

class SpaceScene;

class Environment {
public:
    Environment(SpaceScene* scene);

    Ogre::SceneNode* createCamera();

    Ogre::SceneNode* createLight() const;

    void createDummy() const;

    std::shared_ptr<Fighter> createStarFighter();

    Ogre::SceneNode* createStarship() const;

    Ogre::SceneNode* createAsteroids() const;

    Ogre::SceneNode* createEarth() const;

private:
    SpaceScene* m_scene;
    core::CustomSceneManager* m_sceneManager = nullptr;
};

} // namespace game
