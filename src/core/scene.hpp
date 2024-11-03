#pragma once

#include <OGRE/Ogre.h>

#include "custom_scene_manager.hpp"
#include "custom_scene_node.hpp"
#include "game_event_listener.hpp"

namespace core {

class Scene : public GameEventListener {
public:
    ~Scene() override = default;

    virtual void init();

    Ogre::Camera* mainCamera = nullptr;

    void update(float dt) override;

protected:
    CustomSceneNode* m_rootNode = nullptr;
    CustomSceneManager* m_sceneManager = nullptr;
};

} // end namespace core