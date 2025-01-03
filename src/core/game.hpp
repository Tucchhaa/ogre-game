#pragma once

#include <OGRE/Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreOverlayManager.h>

#include "game_loop_thread.hpp"
#include "scene/custom_scene_manager.hpp"
#include "scene/scene.hpp"
#include "network/network_manager.hpp"

namespace OgreBites
{
    class TrayManager;
}

namespace core {

class Input;
class WindowManager;
class UIManager;
class Scene;
class PhysicsWorld;
class NetworkBase;
class GameLoopThread;

class Game {
public:
    virtual ~Game() = default;

    // To prevent copying
    Game(Game const&) = delete;
    // To prevent copying
    void operator=(Game const&) = delete;

    Game() { _instance.reset(this); }

    static Game& instance() { return *_instance; }

    void configure();

    virtual void init();

    void stop() const;

    // ===
    // Static getters
    // ===

    static int windowWidth();
    static int windowHeight();

    static OgreBites::ApplicationContext* appContext() { return instance().m_ctx; }
    static Ogre::Root* root() { return instance().m_root; }
    static Ogre::RTShader::ShaderGenerator* shaderGenerator() { return instance().m_shaderGenerator; }
    static CustomSceneManager* sceneManager() { return instance().m_scene->sceneManager(); }
    static Ogre::MaterialManager* materialManager() { return instance().m_materialManager; }
    static Ogre::MeshManager* meshManager() { return instance().m_meshManager; }
    static Ogre::RenderWindow* renderWindow() { return instance().m_renderWindow; }
    static Ogre::OverlayManager* overlayManager() { return instance().m_overlayManager; }
    static OgreBites::TrayManager* trayManager() { return instance().m_trayManager; }

    static std::shared_ptr<Input> input() { return instance().m_input; }
    static std::shared_ptr<WindowManager> windowManager() { return instance().m_windowManager; }
    static std::shared_ptr<UIManager> UIManager() { return instance().m_UIManager; }
    static std::shared_ptr<Scene> scene() { return instance().m_scene; }
    static const std::unique_ptr<PhysicsWorld>& physics() { return instance().m_scene->physics(); }
    static std::shared_ptr<NetworkManager> networkManager() { return instance().m_networkManager; }
    static std::shared_ptr<GameLoopThread> gameLoopThread() { return instance().m_gameLoopThread; }
    static bool debugMode() { return instance().m_debugMode; }

    static long long previousUpdateTimestamp();
    static long long currentUpdateTimestamp();

    // ===
    // Setters
    // ===

    void setScene(const std::shared_ptr<Scene>& scene);

    static void setGameLoopThread(const std::shared_ptr<GameLoopThread>& gameLoopThread)
        { instance().m_gameLoopThread = gameLoopThread; }

    /**
     * When debug mode is enabled, the game will draw collider shapes
     */
    bool debugMode(bool value);

private:
    static std::shared_ptr<Game> _instance;

    bool m_debugMode = false;

    OgreBites::ApplicationContext* m_ctx = nullptr;
    Ogre::Root* m_root = nullptr;
    Ogre::RTShader::ShaderGenerator* m_shaderGenerator = nullptr;
    Ogre::MaterialManager* m_materialManager = nullptr;
    Ogre::MeshManager* m_meshManager = nullptr;
    Ogre::RenderWindow* m_renderWindow = nullptr;
    Ogre::OverlayManager* m_overlayManager = nullptr;
    OgreBites::TrayManager* m_trayManager = nullptr;

    std::shared_ptr<Input> m_input;
    std::shared_ptr<WindowManager> m_windowManager;
    std::shared_ptr<core::UIManager> m_UIManager;
    std::shared_ptr<Scene> m_scene;
    std::shared_ptr<NetworkManager> m_networkManager;

    std::shared_ptr<GameLoopThread> m_gameLoopThread;

    class Listener : public Ogre::FrameListener {
    public:
        bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;

        bool frameEnded(const Ogre::FrameEvent& evt) override;
    };
};

} // end namespace core
