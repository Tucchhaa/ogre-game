#include "menu_scene.hpp"

#include "../../core/game.hpp"
#include "../../core/ui_manager.hpp"

namespace game {

void MenuScene::init() {
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

void MenuScene::start() {
    core::Game::UIManager()->showOnly("MAIN_MENU");
}

} // end namespace game
