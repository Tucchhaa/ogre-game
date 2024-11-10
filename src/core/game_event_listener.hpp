#pragma once

#include <map>

namespace core {

class GameEventListener {
public:
    GameEventListener(): ID(generateID()) {
        m_instances[ID] = this;
    }

    virtual ~GameEventListener() {
        m_instances.erase(m_instances.find(ID));
    }

    /**
     * Called before first frame rendered.
     */
    virtual void sceneInited() {}

    /**
     * Called each frame. Triggered by @Ogre::FrameListener::frameRenderingQueued
     */
    virtual void update(float dt) {}

    /**
     * Invoked at fixed rate. All logic must be implemented here.
     * Note: This function is called in a different thread (not main thread),
     * so be careful about concurrency
     */
    virtual void fixedUpdate(float dt) {}

    static void callSceneInited() {
        for(const auto& [ID, instance]: m_instances)
            instance->sceneInited();
    }

    static void callUpdate(float dt) {
        for(const auto& [ID, instance]: m_instances)
            instance->update(dt);
    }

    static void callFixedUpdate(float dt) {
        for(const auto& [ID, instance]: m_instances)
            instance->fixedUpdate(dt);
    }

private:
    int ID;

    static std::map<int, GameEventListener*> m_instances;

    static int generateID() {
        static int lastID = 0;
        return ++lastID;
    }
};

}
