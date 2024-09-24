#pragma once

#include <OGRE/Ogre.h>

namespace core {

class Scene {
public:
    virtual ~Scene() = default;

    virtual void init();

    Ogre::Camera* mainCamera = nullptr;

protected:
    Ogre::SceneNode* m_rootNode = nullptr;
    Ogre::SceneManager* m_sceneManager = nullptr;
};

} // end namespace core