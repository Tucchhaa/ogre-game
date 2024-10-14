#pragma once

#include <OGRE/Ogre.h>

#include "game_event_listener.hpp"

namespace core {

class Scene : public GameEventListener {
public:
    ~Scene() override = default;

    virtual void init();

    Ogre::Camera* mainCamera = nullptr;

    void update(float dt) override;

protected:
    Ogre::SceneNode* m_rootNode = nullptr;
    Ogre::SceneManager* m_sceneManager = nullptr;
};

} // end namespace core