#pragma once

#include <OGRE/Ogre.h>
#include <OgreApplicationContext.h>

#include "custom_scene_manager.hpp"
#include "network_layer/network_layer_manager.hpp"

namespace core {

class Input;
class WindowManager;
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

    void startRendering() const;

    void stopRendering() const;

    void startNetwork() const;

    // ===
    // Static getters
    // ===

    static OgreBites::ApplicationContext* appContext() { return instance().m_ctx; }
    static Ogre::Root* root() { return instance().m_root; }
    static CustomSceneManager* sceneManager() { return instance().m_sceneManager; }
    static Ogre::MaterialManager* materialManager() { return instance().m_materialManager; }
    static Ogre::RenderWindow* renderWindow() { return instance().m_renderWindow; }

    static std::shared_ptr<Input> input() { return instance().m_input; }
    static std::shared_ptr<WindowManager> windowManager() { return instance().m_windowManager; }
    static std::shared_ptr<Scene> scene() { return instance().m_scene; }
    static std::shared_ptr<PhysicsWorld> physics() { return instance().m_physics; }
    static std::shared_ptr<NetworkLayerManager> networkLayerManager() { return instance().m_networkLayerManager; }
    static std::shared_ptr<NetworkLayer> networkLayer() { return networkLayerManager()->networkLayer(); }
    static bool debugMode() { return instance().m_debugMode; }

    // ===
    // Setters
    // ===

    void scene(const std::shared_ptr<Scene>& scene) { m_scene = scene; }

    /**
     * When debug mode is enabled, the game will draw collider shapes
     */
    bool debugMode(bool value);

private:
    bool m_debugMode = false;

    OgreBites::ApplicationContext* m_ctx = nullptr;
    Ogre::Root* m_root = nullptr;
    CustomSceneManager* m_sceneManager = nullptr;
    Ogre::MaterialManager* m_materialManager = nullptr;
    Ogre::RenderWindow* m_renderWindow = nullptr;

    std::shared_ptr<Input> m_input;
    std::shared_ptr<WindowManager> m_windowManager;
    std::shared_ptr<Scene> m_scene;
    std::shared_ptr<PhysicsWorld> m_physics;
    std::shared_ptr<NetworkLayerManager> m_networkLayerManager;

    class Listener : public Ogre::FrameListener {
    public:
        bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;

        bool frameEnded(const Ogre::FrameEvent& evt) override;
    };
};

} // end namespace core