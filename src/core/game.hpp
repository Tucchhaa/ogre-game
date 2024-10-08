#pragma once

#include <OGRE/Ogre.h>
#include <OgreApplicationContext.h>

#include "network_layer/network_layer_manager.hpp"

using namespace std;

namespace core {

class Input;
class Scene;
class PhysicsWorld;
class NetworkLayer;

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

    void stop() const;

    // ===
    // Static getters
    // ===

    static OgreBites::ApplicationContext* appContext() { return instance().m_ctx; }
    static Ogre::Root* root() { return instance().m_root; }
    static Ogre::SceneManager* sceneManager() { return instance().m_sceneManager; }
    static Ogre::MaterialManager* materialManager() { return instance().m_materialManager; }
    static Ogre::RenderWindow* renderWindow() { return instance().m_renderWindow; }

    static shared_ptr<Input> input() { return instance().m_input; }
    static shared_ptr<Scene> scene() { return instance().m_scene; }
    static shared_ptr<PhysicsWorld> physics() { return instance().m_physics; }
    static shared_ptr<NetworkLayerManager> networkLayerManager() { return instance().m_networkLayerManager; }
    static shared_ptr<NetworkLayer> networkLayer() { return networkLayerManager()->networkLayer(); }
    static bool debugMode() { return instance().m_debugMode; }

    // ===
    // Setters
    // ===

    void scene(const shared_ptr<Scene>& scene) { m_scene = scene; }

    /**
     * When debug mode is enabled, the game will draw collider shapes
     */
    bool debugMode(bool value);

private:
    bool m_debugMode = false;

    OgreBites::ApplicationContext* m_ctx = nullptr;
    Ogre::Root* m_root = nullptr;
    Ogre::SceneManager* m_sceneManager = nullptr;
    Ogre::MaterialManager* m_materialManager = nullptr;
    Ogre::RenderWindow* m_renderWindow = nullptr;

    shared_ptr<Input> m_input;
    shared_ptr<Scene> m_scene;
    shared_ptr<PhysicsWorld> m_physics;
    shared_ptr<NetworkLayerManager> m_networkLayerManager;

    class Listener : public Ogre::FrameListener {
    public:
        bool frameEnded(const Ogre::FrameEvent& evt) override;
    };
};

} // end namespace core