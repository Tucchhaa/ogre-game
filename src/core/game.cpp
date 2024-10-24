#include "game.hpp"

#include "game_event_listener.hpp"
#include "objects/collider.hpp"
#include "objects/free_character_controller.hpp"

#include "scene.hpp"
#include "input.hpp"
#include "physics_world.hpp"
#include "window_manager.hpp"
#include "network_layer/network_layer_manager.hpp"

namespace core {

void Game::configure() {
    const string projectPath = filesystem::current_path().parent_path();

    setenv("OGRE_CONFIG_DIR", projectPath.c_str(), 1);

    m_ctx = new OgreBites::ApplicationContext("OgreTutorialApp");
}

void Game::init() {
    m_ctx->initApp();

    m_root = m_ctx->getRoot();
    m_root->addMovableObjectFactory(new FreeCameraControllerFactory);
    m_root->addMovableObjectFactory(new ColliderFactory);
    m_root->addFrameListener(new Listener);

    m_sceneManager = m_root->createSceneManager();
    m_materialManager = Ogre::MaterialManager::getSingletonPtr();
    m_renderWindow = m_ctx->getRenderWindow();

    m_windowManager = make_shared<WindowManager>();
    m_input = make_shared<Input>();
    m_physics = make_shared<PhysicsWorld>();
    m_networkLayerManager = make_shared<NetworkLayerManager>();

    const auto shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shaderGenerator->addSceneManager(m_sceneManager);

    m_ctx->addInputListener(m_input.get());
}

void Game::start() const {
    m_networkLayerManager->initNetworkLayer(GameType::SinglePlayer);
    m_scene->init();
    m_renderWindow->addViewport(m_scene->mainCamera);

    m_networkLayerManager->start();
    m_root->startRendering();
}

void Game::stop() const {
    m_root->queueEndRendering();
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
