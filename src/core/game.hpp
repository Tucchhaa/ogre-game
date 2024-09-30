#pragma once

#include <OGRE/Ogre.h>
#include <OgreApplicationContext.h>

#include "input.hpp"
#include "physics_world.hpp"

using namespace std;

namespace core {

class Scene;

class Game {
public:
    static Game& instance() {
        static Game _instance;
        return _instance;
    }

    // To prevent copying
    Game(Game const&) = delete;
    // To prevent copying
    void operator=(Game const&) = delete;

    Game() = default;

    void configure();

    void init();

    void start() const;

    // ===
    // Static getters
    // ===
    static OgreBites::ApplicationContext* appContext() { return instance().m_ctx; }
    static Ogre::Root* root() { return instance().m_ctx->getRoot(); }
    static Ogre::SceneManager* sceneManager() { return instance().m_sceneManager; }
    static Ogre::MaterialManager* materialManager() { return instance().m_materialManager; }
    static shared_ptr<Input> input() { return instance().m_input; }
    static shared_ptr<Scene> scene() { return instance().m_scene; }
    static shared_ptr<PhysicsWorld> physics() { return instance().m_physics; }
    static bool debugMode() { return instance().m_debugMode; }

    // ===
    // Setters
    // ===
    void scene(const shared_ptr<Scene>& scene) { m_scene = scene; }
    /**
     * When debug mode is enabled, the game will draw collider shapes
     */
    bool debugMode(bool value) { return m_debugMode = value; }

private:
    bool m_debugMode = false;

    OgreBites::ApplicationContext* m_ctx = nullptr;
    Ogre::SceneManager* m_sceneManager = nullptr;
    Ogre::MaterialManager* m_materialManager = nullptr;

    shared_ptr<Input> m_input;
    shared_ptr<Scene> m_scene;
    shared_ptr<PhysicsWorld> m_physics;
};

} // end namespace core