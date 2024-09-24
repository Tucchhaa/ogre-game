#include "game.hpp"

#include "scene.hpp"
#include "objects/free_character_controller.hpp"

namespace core {

void Game::configure() {
    const string projectPath = filesystem::current_path().parent_path();

    setenv("OGRE_CONFIG_DIR", projectPath.c_str(), 1);

    m_ctx = new OgreBites::ApplicationContext("OgreTutorialApp");
}

void Game::init() {
    m_ctx->initApp();

    Ogre::Root* root = m_ctx->getRoot();
    root->addMovableObjectFactory(new FreeCameraControllerFactory);

    m_sceneManager = root->createSceneManager();

    const auto shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shaderGenerator->addSceneManager(m_sceneManager);

    m_input = make_shared<Input>();
    m_ctx->addInputListener(m_input.get());

    // scene must initiated last
    m_scene->init();
    m_ctx->getRenderWindow()->addViewport(m_scene->mainCamera);
}

void Game::start() const {
    m_ctx->getRoot()->startRendering();
}

} // end namespace core
