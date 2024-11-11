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

#include "utils.hpp"

namespace core {

std::shared_ptr<Game> Game::_instance = nullptr;

void Game::configure() {
    const std::filesystem::path projectPath = std::filesystem::current_path().parent_path();

    #ifdef _WIN32
        putenv(("OGRE_CONFIG_DIR=" + projectPath.string()).c_str());
    #elif __APPLE__
        setenv("OGRE_CONFIG_DIR", projectPath.c_str(), 1);
    #endif

    const auto appName = utils::isClientExecutable() ? "OgreClient" : "OgreServer";
    m_ctx = new OgreBites::ApplicationContext(appName);
}

void Game::init() {
    m_ctx->initApp();

    m_root = m_ctx->getRoot();
    m_root->addMovableObjectFactory(new FreeCameraControllerFactory);
    m_root->addMovableObjectFactory(new ColliderFactory);
    m_root->addMovableObjectFactory(new TransformFactory);
    m_root->addSceneManagerFactory(new CustomSceneManagerFactory);
    m_root->addFrameListener(new Listener);

    m_materialManager = Ogre::MaterialManager::getSingletonPtr();
    m_renderWindow = m_ctx->getRenderWindow();
    m_trayManager = new OgreBites::TrayManager("MainTray", m_renderWindow);

    m_windowManager = std::make_shared<WindowManager>();
    m_UIManager = std::make_shared<core::UIManager>();
    m_input = std::make_shared<Input>();
    m_networkLayerManager = std::make_shared<NetworkLayerManager>();

    m_shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

    m_ctx->addInputListener(m_input.get());
    m_ctx->addInputListener(m_trayManager);
}

void Game::stop() const {
    m_root->queueEndRendering();
}

void Game::startNetwork() const {
    if(utils::isClientExecutable()) {
        m_networkLayerManager->searchLANGames();
        m_networkLayerManager->initNetworkLayer(NetworkType::LANPeer);
    }
    else {
        m_networkLayerManager->initNetworkLayer(NetworkType::LANHost);
    }

    m_networkLayerManager->start();
}

void Game::setScene(const std::shared_ptr<Scene>& scene) {
    const auto oldScene = m_scene;

    m_scene = scene;
    m_scene->init();

    m_renderWindow->removeAllViewports();
    m_renderWindow->addViewport(m_scene->mainCamera);

    if(oldScene != nullptr) {
        oldScene->sceneManager()->destroyCamera(oldScene->mainCamera);
        oldScene->mainCamera = nullptr;

        GameEventListener::callSceneInited();
        m_scene->start();
    }
    // if there is no old scene, then this scene is first, and we need to start rendering
    else {
        startNetwork();
        GameEventListener::callSceneInited();
        m_scene->start();
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
        networkLayerManager()->stop();
        appContext()->closeApp();
        return false;
    }

    return true;
}

} // end namespace core
