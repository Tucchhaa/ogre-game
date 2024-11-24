#include "space_scene.hpp"

#include "core/objects/collider.hpp"
#include "game/objects/star_fighter_controller.hpp"

void game::SpaceScene::init() {
    Scene::init();

    m_physics->dynamicsWorld()->setGravity(btVector3(0, 0, 0));

    m_sceneManager->setSkyBox(true, "Skybox/Starfield", 10000, true);

    createCamera();
    createLight();
    createDummy();
    createStarFighter();
    createEarth();
}

void game::SpaceScene::createCamera() {
    auto* cameraNode = m_rootNode->createChildSceneNode("CameraNode");
    cameraNode->setPosition(0, 0, 15);
    cameraNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    mainCamera = m_sceneManager->createCamera("Camera");
    mainCamera->setNearClipDistance(0.1);
    mainCamera->setAutoAspectRatio(true);
    cameraNode->attachObject(mainCamera);
}

void game::SpaceScene::createLight() const {
    auto* light = m_sceneManager->createLight("MainLight");
    light->setType(Ogre::Light::LT_DIRECTIONAL);

    auto* lightNode = m_rootNode->createChildSceneNode("MainLightNode");
    lightNode->setPosition(0, 20, 15);
    lightNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
    lightNode->attachObject(light);
}

void game::SpaceScene::createDummy() const {
    auto* shipEntity = m_sceneManager->createEntity("DummyShipEntity", "assets/star_fighters/StarFighter03.fbx");
    shipEntity->getMesh()->buildTangentVectors();
    shipEntity->setMaterialName("StarFighter_RTSS");

    auto* shipNode = m_rootNode->createChildSceneNode("DummyShipNode");
    shipNode->scale(0.01, 0.01, 0.01);
    shipNode->translate(40, 0, 40);
    shipNode->attachObject(shipEntity);
}

void game::SpaceScene::createStarFighter() const {
    auto* shipNodeWrapper = m_rootNode->createChildSceneNode("ShipNodeWrapper");

    auto box = core::Shape(std::make_shared<btBoxShape>(btVector3(2, 1, 5)));
    auto* colliderObj = m_sceneManager->createMovableObject("ShipCollider", "Collider");
    auto* collider = static_cast<core::Collider*>(colliderObj);
    collider->setShapes({ box });
    collider->rigidbody()->setActivationState(DISABLE_DEACTIVATION);

    auto* shipController = m_sceneManager->createMovableObject("StarFighterController");
    static_cast<StarFighterController*>(shipController)->setCollider(collider);

    shipNodeWrapper->attachObject(collider);
    shipNodeWrapper->attachObject(shipController);

    auto* shipEntity = m_sceneManager->createEntity("ShipEntity", "assets/star_fighters/StarFighter01.fbx");
    shipEntity->getMesh()->buildTangentVectors();
    shipEntity->setMaterialName("StarFighter_RTSS");

    auto* shipNode = shipNodeWrapper->createChildSceneNode("ShipNode");
    shipNode->scale(0.01, 0.01, 0.01);
    shipNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(180));
    shipNode->attachObject(shipEntity);
}

void game::SpaceScene::createEarth() const {
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
