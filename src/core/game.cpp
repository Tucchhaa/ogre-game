#include "game.hpp"

#include <filesystem>

#include "custom_scene_manager.hpp"
#include "game_event_listener.hpp"
#include "scene.hpp"
#include "input.hpp"
#include "physics_world.hpp"
#include "window_manager.hpp"
#include "network_layer/network_layer_manager.hpp"

#include "objects/collider.hpp"
#include "objects/free_character_controller.hpp"
#include "objects/transform.hpp"

#include "utils.hpp"

namespace core {

void Game::configure() {
    const std::filesystem::path projectPath = std::filesystem::current_path().parent_path();

    #ifdef _WIN32
        putenv(("OGRE_CONFIG_DIR=" + projectPath.string()).c_str());
    #elif __APPLE__
        setenv("OGRE_CONFIG_DIR", projectPath.c_str(), 1);
    #endif

    const auto appName = "OgreTutorialApp";
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

    m_sceneManager = static_cast<CustomSceneManager*>(m_root->createSceneManager(CUSTOM_SCENE_MANAGER_TYPE));
    m_materialManager = Ogre::MaterialManager::getSingletonPtr();
    m_renderWindow = m_ctx->getRenderWindow();

    m_windowManager = std::make_shared<WindowManager>();
    m_input = std::make_shared<Input>();
    m_physics = std::make_shared<PhysicsWorld>();
    m_networkLayerManager = std::make_shared<NetworkLayerManager>();

    const auto shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shaderGenerator->addSceneManager(m_sceneManager);

    m_ctx->addInputListener(m_input.get());
}

void Game::startRendering() const {
    m_scene->init();
    m_renderWindow->addViewport(m_scene->mainCamera);
    m_sceneManager->_updateSceneGraph(m_scene->mainCamera);
    GameEventListener::callStart();
    m_root->startRendering();
}

void Game::stopRendering() const {
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
