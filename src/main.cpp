#include <iostream>

#include "core/game.hpp"
#include "core/input.hpp"
#include "core/scene.hpp"
#include "core/window_manager.hpp"
#include "core/objects/collider.hpp"

using namespace std;

class SimpleScene : public core::Scene {
    void init() override {
        core::Game::windowManager()->relativeMouseEnabled(true);

        Scene::init();

        // without light we would just get a black screen
        Ogre::Light* light = m_sceneManager->createLight("MainLight");
        Ogre::SceneNode* lightNode = m_rootNode->createChildSceneNode();
        lightNode->setPosition(0, 10, 15);
        lightNode->attachObject(light);

        // also need to tell where we are
        Ogre::SceneNode* cameraNode = m_rootNode->createChildSceneNode();
        cameraNode->setPosition(0, 0, 15);
        cameraNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

        // create the camera
        mainCamera = m_sceneManager->createCamera("myCam");
        mainCamera->setNearClipDistance(5); // specific to this sample
        mainCamera->setAutoAspectRatio(true);
        cameraNode->attachObject(mainCamera);

        // create controller
        auto* controller = m_sceneManager->createMovableObject("FreeCameraController");
        cameraNode->attachObject(controller);

        // finally something to render
//        Ogre::Entity* ent = m_sceneManager->createEntity("Sinbad/Sinbad.mesh");
//
//        Ogre::SceneNode* sinbadNode = m_rootNode->createChildSceneNode();
//        sinbadNode->translate(Ogre::Vector3(0, 4, 0));
//        sinbadNode->attachObject(ent);
//        // sinbad collider
//        auto sinbadColliderShape = core::Shape(
//            make_shared<btBoxShape>(btVector3(2, 4.5, 1))
//        );
//        sinbadColliderShape.transform()->setOrigin(btVector3(0, -0.35, 0));
//        auto sinbadCollider = dynamic_cast<core::Collider*>(m_sceneManager->createMovableObject("SinbadCollider", "Collider"));
//        sinbadCollider->setShapes({ sinbadColliderShape });
//        sinbadNode->attachObject(sinbadCollider);

        // ground
        Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
        Ogre::MeshManager::getSingleton().createPlane(
            "ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
            1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z
        );
        Ogre::Entity* groundEntity = m_sceneManager->createEntity("ground");
        groundEntity->setCastShadows(false);

        auto* groundNode = m_rootNode->createChildSceneNode();
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

int main()
{
    const auto scene = make_shared<SimpleScene>();

    auto& game = core::Game::instance();
    game.debugMode(true);
    game.configure();
    game.init();
    game.scene(scene);

    game.startNetwork();
    game.startRendering();

    return 0;
}
