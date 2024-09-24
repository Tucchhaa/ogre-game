#include <iostream>

#include "core/game.hpp"
#include "core/scene.hpp"

using namespace std;

class SimpleScene : public core::Scene {
    void init() override {
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
        Ogre::Entity* ent = m_sceneManager->createEntity("Sinbad/Sinbad.mesh");
        Ogre::SceneNode* node = m_rootNode->createChildSceneNode();
        node->attachObject(ent);

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
    }
};

int main()
{
    const auto scene = make_shared<SimpleScene>();

    auto& game = core::Game::instance();
    game.configure();
    game.scene(scene);
    game.init();
    game.start();

    return 0;
}
