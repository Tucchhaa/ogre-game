#include "game.hpp"

#include "objects/collider.hpp"
#include "objects/free_character_controller.hpp"

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

    m_sceneManager = m_root->createSceneManager();
    m_materialManager = Ogre::MaterialManager::getSingletonPtr();
    m_renderWindow = m_ctx->getRenderWindow();

    m_input = make_shared<Input>();
    m_physics = make_shared<PhysicsWorld>();
    m_networkLayerManager = make_shared<NetworkLayerManager>();

    // TODO: remove this line
    m_networkLayerManager->init(GameType::SinglePlayer);

    const auto shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shaderGenerator->addSceneManager(m_sceneManager);

    m_ctx->addInputListener(m_input.get());

    // scene must initiated last
    m_scene->init();
    m_renderWindow->addViewport(m_scene->mainCamera);
}

void Game::start() const {
    m_networkLayerManager->start();
    m_root->startRendering();
}

void Game::stop() const {
    m_root->queueEndRendering();
}

} // end namespace core
