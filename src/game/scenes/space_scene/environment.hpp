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
class Starship;
class Fighter;

class SpaceScene;

class Environment {
public:
    Environment(SpaceScene* scene);

    Ogre::SceneNode* createCamera();

    Ogre::SceneNode* createLight() const;

    void createDummy() const;

    std::shared_ptr<Fighter> createStarFighter();

    std::shared_ptr<Starship> createRedStarship() const;

    std::shared_ptr<Starship> createBlueStarship() const;

    core::CustomSceneNode* createAsteroids() const;

    core::CustomSceneNode* createEarth() const;

private:
    SpaceScene* m_scene;
    core::CustomSceneManager* m_sceneManager = nullptr;

    std::shared_ptr<Starship> createStarship(const std::string& prefix) const;
};

} // namespace game
