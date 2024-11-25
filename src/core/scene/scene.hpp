#pragma once

#include <OGRE/Ogre.h>

#include "custom_scene_manager.hpp"
#include "custom_scene_node.hpp"

#include "../game_event_listener.hpp"
#include "../physics/physics_world.hpp"

namespace core {

class Scene : public GameEventListener {
public:
    Scene();
    ~Scene() override = default;

    CustomSceneManager* sceneManager() const { return m_sceneManager; }
    const std::unique_ptr<PhysicsWorld>& physics() const { return m_physics; }
    CustomSceneNode* root() const { return m_rootNode; }

    virtual void init();

    /**
     * Called before first frame
     */
    virtual void start();

    /**
     * Called when another scene is inited or when game stops
     */
    virtual void stop();

    Ogre::Camera* mainCamera = nullptr;

    /**
     * Do not use this method in Scene class, because it will be called for other scenes too.
     */
    void sceneInited() override {}

    void update(float dt) override;

protected:
    CustomSceneNode* m_rootNode = nullptr;
    CustomSceneManager* m_sceneManager = nullptr;

    std::unique_ptr<PhysicsWorld> m_physics;
};

} // end namespace core