#include <iostream>

#include "core/game.hpp"
#include "core/input.hpp"
#include "core/scene.hpp"
#include "core/window_manager.hpp"
#include "core/objects/collider.hpp"

#include "game/galactic_wars_game.hpp"

using namespace std;

class SimpleScene : public core::Scene {
    void init() override {
        core::Game::windowManager()->relativeMouseEnabled(true);

        Scene::init();

        createLight();
        createCamera();
        createSinbad();
        createGround();
    }

    void createLight() {
        auto* light = m_sceneManager->createLight("MainLight");
        auto* lightNode = m_rootNode->createChildSceneNode("MainLightNode");

        lightNode->setPosition(0, 10, 15);
        lightNode->attachObject(light);
    }

    void createCamera() {
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

    void createSinbad() {
        auto* sinbadEntity = m_sceneManager->createEntity("SinbadEntity", "Sinbad/Sinbad.mesh");

        auto* sinbadNode = m_rootNode->createChildSceneNode("SinbadNode");
        sinbadNode->translate(Ogre::Vector3(0, 4, 0));
        sinbadNode->attachObject(sinbadEntity);

        // sinbad collider
        auto sinbadColliderShape = core::Shape(
            make_shared<btBoxShape>(btVector3(2, 4.5, 1))
        );
        sinbadColliderShape.transform()->setOrigin(btVector3(0, -0.35, 0));
        auto sinbadCollider = dynamic_cast<core::Collider*>(m_sceneManager->createMovableObject("SinbadCollider", "Collider"));
        sinbadCollider->setShapes({ sinbadColliderShape });
        sinbadNode->attachObject(sinbadCollider);
    }

    void createGround() {
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
            make_shared<btBoxShape>(btVector3(100, 1, 100))
        );
        groundColliderShape.transform()->setOrigin(btVector3(0, -1, 0));
        auto groundCollider = dynamic_cast<core::Collider*>(m_sceneManager->createMovableObject("GroundCollider", "Collider"));
        groundCollider->setShapes({ groundColliderShape });
        groundCollider->setMass(0);
        groundNode->attachObject(groundCollider);
    }

    void update(float dt) override {
        Scene::update(dt);

        if(core::Game::input()->isKeyPressed(core::Key::ESCAPE)) {
            core::Game::instance().stopRendering();
        }
        if(core::Game::input()->isKeyDown(core::Key::SPACE)) {
            core::Game::windowManager()->relativeMouseEnabled(
                !core::Game::windowManager()->relativeMouseEnabled()
            );
        }
    }
};

class UIScene : public core::Scene {
    void init() override {
        Scene::init();

        // Create Main Menu Scene.
        // Setup camera.
        mainCamera = m_sceneManager->createCamera("myCamera");
        mainCamera->setNearClipDistance(5); // specific to this sample
        mainCamera->setAutoAspectRatio(true);
        Ogre::SceneNode* camNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
        camNode->setFixedYawAxis(true);
        camNode->setPosition(0, 300, 0);
        camNode->lookAt(Ogre::Vector3(0, 0.001, 0), Ogre::Node::TS_PARENT);
        camNode->attachObject(mainCamera);

        // Now create a plane on x-z plan for background texture menu
        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0); // Y = 0, plane is horizontal
        Ogre::MeshManager::getSingleton().createPlane("MenuPlane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z); // Size and subdivisions

        // Create a scene node to attach the plane to
        Ogre::SceneNode* planeNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
        Ogre::Entity* planeEntity = m_sceneManager->createEntity("backgroundMenuEntity","MenuPlane");
        //planeEntity->setMaterial("sd");
        planeNode->attachObject(planeEntity);

        // Add some Light to show the plan
        Ogre::Light* light = m_sceneManager->createLight("MainLight");
        light->setType(Ogre::Light::LT_POINT);
        light->setDiffuseColour(Ogre::ColourValue::White);
        light->setSpecularColour(Ogre::ColourValue::White);
        Ogre::SceneNode* lightNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(0, 400, 0);
        lightNode->attachObject(light);
    }
};

int main()
{
    const auto scene = make_shared<UIScene>();

    auto game = game::GalacticWarsGame();
    game.configure();
    game.init();
    game.scene(scene);
    game.startNetwork();
    game.startRendering();

    return 0;
}
