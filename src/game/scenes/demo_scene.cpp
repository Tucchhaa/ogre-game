#include "demo_scene.hpp"

#include "../../core/game.hpp"
#include "../../core/window_manager.hpp"
#include "../../core/input.hpp"
#include "../../core/objects/collider.hpp"

namespace game {

void DemoScene::init() {
    core::Game::windowManager()->relativeMouseEnabled(true);

    Scene::init();

    createLight();
    createCamera();
    createSinbad();
    createGround();
}

void DemoScene::createLight() const {
    auto* light = m_sceneManager->createLight("MainLight");
    auto* lightNode = m_rootNode->createChildSceneNode("MainLightNode");

    lightNode->setPosition(0, 10, 15);
    lightNode->attachObject(light);
}

void DemoScene::createCamera() {
    auto* cameraNode = m_rootNode->createChildSceneNode("CameraNode");
    cameraNode->setPosition(0, 0, 15);
    cameraNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    mainCamera = m_sceneManager->createCamera("Camera");
    mainCamera->setNearClipDistance(5); // specific to this sample
    mainCamera->setAutoAspectRatio(true);
    cameraNode->attachObject(mainCamera);

    auto* controller = m_sceneManager->createMovableObject("FreeCameraController");
    cameraNode->attachObject(controller);
}

void DemoScene::createSinbad() {
    auto* sinbadEntity = m_sceneManager->createEntity("SinbadEntity", "Sinbad/Sinbad.mesh");

    auto* sinbadNode = m_rootNode->createChildSceneNode("SinbadNode");
    sinbadNode->translate(Ogre::Vector3(0, 4, 0));
    sinbadNode->attachObject(sinbadEntity);

    // sinbad collider
    auto sinbadColliderShape = core::Shape(
        std::make_shared<btBoxShape>(btVector3(2, 4.5, 1))
    );
    sinbadColliderShape.transform()->setOrigin(btVector3(0, -0.35, 0));
    auto sinbadCollider = dynamic_cast<core::Collider*>(m_sceneManager->createMovableObject("SinbadCollider", "Collider"));
    sinbadCollider->setShapes({ sinbadColliderShape });
    sinbadNode->attachObject(sinbadCollider);
}

void DemoScene::createGround() {
    // ground mesh
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
        "ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
        1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z
    );
    Ogre::Entity* groundEntity = m_sceneManager->createEntity("GroundEntity", "ground");
    groundEntity->setCastShadows(false);

    auto* groundNode = m_rootNode->createChildSceneNode("GroundNode");
    groundNode->setPosition(Ogre::Vector3(0, -10, 0));
    groundNode->attachObject(groundEntity);

    // ground collider
    auto groundColliderShape = core::Shape(
        std::make_shared<btBoxShape>(btVector3(100, 1, 100))
    );
    groundColliderShape.transform()->setOrigin(btVector3(0, -1, 0));
    auto groundCollider = dynamic_cast<core::Collider*>(m_sceneManager->createMovableObject("GroundCollider", "Collider"));
    groundCollider->setShapes({ groundColliderShape });
    groundCollider->setMass(0);
    groundNode->attachObject(groundCollider);
}

void DemoScene::update(float dt) {
    Scene::update(dt);

    if(core::Game::input()->isKeyPressed(core::Key::ESCAPE)) {
        core::Game::instance().stop();
    }
    if(core::Game::input()->isKeyDown(core::Key::SPACE)) {
        core::Game::windowManager()->relativeMouseEnabled(
            !core::Game::windowManager()->relativeMouseEnabled()
        );
    }
}

} // end namespace game
