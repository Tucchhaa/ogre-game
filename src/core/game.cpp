#include "game.hpp"

#include <filesystem>
#include <Bites/OgreTrays.h>

#include "game_event_listener.hpp"
#include "scene/custom_scene_manager.hpp"
#include "scene/scene.hpp"
#include "input.hpp"
#include "ui_manager.hpp"
#include "window_manager.hpp"
#include "network/network_manager.hpp"

#include "objects/collider.hpp"
#include "objects/free_character_controller.hpp"
#include "objects/transform.hpp"

namespace core {

std::shared_ptr<Game> Game::_instance = nullptr;

void Game::configure() {
    const std::filesystem::path projectPath = std::filesystem::current_path().parent_path();

    #ifdef _WIN32
        putenv(("OGRE_CONFIG_DIR=" + projectPath.string()).c_str());
    #elif __APPLE__
        setenv("OGRE_CONFIG_DIR", projectPath.c_str(), 1);
    #endif

    m_ctx = new OgreBites::ApplicationContext("GalacticWars");
}

void Game::init() {
    m_ctx->initApp();

    m_root = m_ctx->getRoot();
    m_root->addMovableObjectFactory(new FreeCameraControllerFactory);
    m_root->addMovableObjectFactory(new ColliderFactory);
    m_root->addMovableObjectFactory(new TransformFactory);
    m_root->addSceneManagerFactory(new CustomSceneManagerFactory);
    m_root->addFrameListener(new Listener);

    m_shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    m_shaderGenerator->initialize();

    m_materialManager = Ogre::MaterialManager::getSingletonPtr();
    m_meshManager = Ogre::MeshManager::getSingletonPtr();
    m_renderWindow = m_ctx->getRenderWindow();
    m_overlayManager = Ogre::OverlayManager::getSingletonPtr();
    m_trayManager = new OgreBites::TrayManager("MainTray", m_renderWindow);

    m_windowManager = std::make_shared<WindowManager>();
    m_UIManager = std::make_shared<core::UIManager>();
    m_input = std::make_shared<Input>();
    m_networkManager = std::make_shared<NetworkManager>();

    m_ctx->addInputListener(m_input.get());
    m_ctx->addInputListener(m_trayManager);
}

void Game::stop() const {
    m_root->queueEndRendering();
}

int Game::windowWidth() {
    return renderWindow()->getViewport(0)->getActualWidth();
}

int Game::windowHeight() {
    return renderWindow()->getViewport(0)->getActualHeight();
}

long long Game::previousUpdateTimestamp() {
    auto gameLoopThread = instance().m_gameLoopThread;
    return gameLoopThread == nullptr ? 0 : gameLoopThread->previousUpdateTimestamp();
}

long long Game::currentUpdateTimestamp() {
    auto gameLoopThread = instance().m_gameLoopThread;
    return gameLoopThread == nullptr ? 0 : gameLoopThread->currentUpdateTimestamp();
}

void Game::setScene(const std::shared_ptr<Scene>& scene) {
    const auto oldScene = m_scene;

    m_scene = scene;
    m_scene->init();

    m_renderWindow->removeAllViewports();
    m_renderWindow->addViewport(m_scene->mainCamera);

    GameEventListener::callSceneInited();
    m_scene->start();

    if (m_gameLoopThread && m_gameLoopThread->type() == GameLoopThread::GameLoopType::SinglePlayer) {
        m_gameLoopThread->start();
    }

    if(oldScene != nullptr) {
        oldScene->sceneManager()->destroyCamera(oldScene->mainCamera);
        oldScene->mainCamera = nullptr;
    }
    // if there is no old scene, then this scene is the entry point, and we need to start rendering
    else {
        m_root->startRendering();
    }
}

bool Game::debugMode(bool value) {
    return m_debugMode = value;
}

bool Game::Listener::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    GameEventListener::callUpdate(evt.timeSinceLastFrame);
    input()->updateInputState();

    return true;
}

bool Game::Listener::frameEnded(const Ogre::FrameEvent& evt) {
    if(root()->endRenderingQueued()) {
        networkManager()->stop();
        appContext()->closeApp();
        return false;
    }

    return true;
}

} // end namespace core
