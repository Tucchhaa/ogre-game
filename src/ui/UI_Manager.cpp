//
// Created by vince on 03/11/2024.
//

#include "UI_Manager.h"

#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <SDL_main.h>

#include "lan_menu.h"
#include "main_menu.h"

UI_Manager::UI_Manager(Ogre::Root* root, Ogre::SceneManager* scene_manager, OgreBites::TrayManager* tray_manager)
{
    m_root = root;
    m_scene_manager = scene_manager;
    m_tray_manager = tray_manager;
    m_tray_manager->setListener(this);
    createMenuScene();

    init_LanMenu();
    init_MainMenu();

    show_MainMenu();
}

void UI_Manager::createMenuScene()
{
    // Clear the current scene.
    m_scene_manager->clearScene();

    // Create Main Menu Scene.
    // Setup camera.
    m_camera = m_scene_manager->createCamera("myCamera");
    m_camera->setNearClipDistance(5); // specific to this sample
    m_camera->setAutoAspectRatio(true);
    Ogre::SceneNode* camNode = m_scene_manager->getRootSceneNode()->createChildSceneNode();
    camNode->setFixedYawAxis(true);
    camNode->setPosition(0, 300, 0);
    camNode->lookAt(Ogre::Vector3(0, 0.001, 0), Ogre::Node::TS_PARENT);
    camNode->attachObject(m_camera);

    // Now create a plane on x-z plan for background texture menu
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0); // Y = 0, plane is horizontal
    Ogre::MeshManager::getSingleton().createPlane("MenuPlane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z); // Size and subdivisions

    // Create a scene node to attach the plane to
    Ogre::SceneNode* planeNode = m_scene_manager->getRootSceneNode()->createChildSceneNode();
    Ogre::Entity* planeEntity = m_scene_manager->createEntity("backgroundMenuEntity","MenuPlane");
    //planeEntity->setMaterial("sd");
    planeNode->attachObject(planeEntity);

    // Add some Light to show the plan
    Ogre::Light* light = m_scene_manager->createLight("MainLight");
    light->setType(Ogre::Light::LT_POINT);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue::White);
    Ogre::SceneNode* lightNode = m_scene_manager->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 400, 0);
    lightNode->attachObject(light);
}

void UI_Manager::init_MainMenu()
{
    main_menu_tray_listener = new MainMenu(m_root, m_tray_manager, this);
}
void UI_Manager::init_LanMenu()
{
    lan_tray_listener = new LAN_Menu(m_tray_manager, this);
}

void UI_Manager::buttonHit(OgreBites::Button* button)
{
    current_tray_listener->buttonHit(button);
}

void UI_Manager::show_LanMenu()
{
    m_tray_manager->destroyAllWidgets();
    lan_tray_listener->initOverlay();
    current_tray_listener = lan_tray_listener;
}

void UI_Manager::show_MainMenu()
{
    m_tray_manager->destroyAllWidgets();
    main_menu_tray_listener->initOverlay();
    current_tray_listener = main_menu_tray_listener;
}

Ogre::Camera* UI_Manager::getCamera()
{
    return m_camera;
}
