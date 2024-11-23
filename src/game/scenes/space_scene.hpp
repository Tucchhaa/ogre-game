#pragma once

#include "../../core/scene/scene.hpp"

namespace game {

class SpaceScene : public core::Scene {
    void init() override {
        Scene::init();

        m_sceneManager->setSkyBox(true, "Skybox/Space1_1K", 10000, true);

        createCamera();
        createLight();
        // createGround();

        auto* shipEntity = m_sceneManager->createEntity("ShipEntity", "assets/star_fighters/StarFighter01.fbx");
        shipEntity->getMesh()->buildTangentVectors();
        shipEntity->setMaterialName("StarFighter_RTSS");
        auto* shipNode = m_rootNode->createChildSceneNode("ShipNode");

        shipNode->scale(0.01, 0.01, 0.01);
        shipNode->attachObject(shipEntity);

        // planet
        auto* earthEntity = m_sceneManager->createEntity("EarthEntity", "assets/earth/earth.fbx");
        earthEntity->getSubEntities()[0]->setMaterialName("EarthPlanet_RTSS");
        earthEntity->getSubEntities()[1]->setMaterialName("EarthClouds_RTSS");
        earthEntity->getSubEntities()[2]->setMaterialName("EarthAtmosphere_RTSS");

        auto* earthNode = m_rootNode->createChildSceneNode("EarthNode");

        earthNode->attachObject(earthEntity);
        earthNode->setPosition(Ogre::Vector3(0, -3000, 0));
        earthNode->setScale(25, 25, 25);
        earthNode->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(90));
        earthNode->rotate(Ogre::Vector3(1, 0, 0), Ogre::Radian(-170));
    }

    void createCamera() {
        auto* cameraNode = m_rootNode->createChildSceneNode("CameraNode");
        cameraNode->setPosition(0, 0, 15);
        cameraNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

        mainCamera = m_sceneManager->createCamera("Camera");
        mainCamera->setNearClipDistance(0.1);
        mainCamera->setAutoAspectRatio(true);
        cameraNode->attachObject(mainCamera);

        auto* controller = m_sceneManager->createMovableObject("FreeCameraController");
        cameraNode->attachObject(controller);
    }

    void createLight() const {
        auto* light = m_sceneManager->createLight("MainLight");
        light->setType(Ogre::Light::LT_DIRECTIONAL);

        auto* lightNode = m_rootNode->createChildSceneNode("MainLightNode");
        lightNode->setPosition(0, 20, 15);
        lightNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
        lightNode->attachObject(light);
    }

    void createGround() {
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
    }

    void start() override {

    }
};

} // end namespace game
