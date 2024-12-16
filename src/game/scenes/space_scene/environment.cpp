#include "environment.hpp"

#include "scene.hpp"
#include "core/utils.hpp"
#include "core/objects/collider.hpp"
#include "core/physics/tools.hpp"
#include "game/galactic_wars_game.hpp"
#include "game/objects/star_fighters/fighter.hpp"

namespace game {

Environment::Environment(SpaceScene* scene): m_scene(scene) {
    m_sceneManager = m_scene->sceneManager();
}

Ogre::SceneNode* Environment::createCamera() {
    auto* cameraNode = m_sceneManager->createSceneNode("CameraNode");
    cameraNode->setPosition(0, 0, 15);
    cameraNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    auto mainCamera = m_sceneManager->createCamera("MainCamera");
    mainCamera->setNearClipDistance(0.1);
    mainCamera->setAutoAspectRatio(true);
    cameraNode->attachObject(mainCamera);

    return cameraNode;
}

Ogre::SceneNode* Environment::createLight() const {
    auto* light = m_sceneManager->createLight("MainLight");
    light->setType(Ogre::Light::LT_DIRECTIONAL);

    auto* lightNode = m_sceneManager->createSceneNode("MainLightNode");
    lightNode->setPosition(0, 20, 15);
    lightNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
    lightNode->attachObject(light);

    m_sceneManager->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));

    return lightNode;
}

void Environment::createDummy() const {
    // auto* shipEntity = m_sceneManager->createEntity("DummyShipEntity", "assets/star_fighters/StarFighter03.fbx");
    // shipEntity->getMesh()->buildTangentVectors();
    // shipEntity->setMaterialName("StarFighter_RTSS");
    //
    // auto* shipNode = m_rootNode->createChildSceneNode("DummyShipNode");
    // shipNode->scale(0.01, 0.01, 0.01);
    // shipNode->translate(40, 0, 40);
    // shipNode->attachObject(shipEntity);
}

std::shared_ptr<Fighter> Environment::createStarFighter() {
    auto fighter = std::make_shared<Fighter>();

    return fighter;
}

Ogre::SceneNode* Environment::createStarship() const {
    auto* entity = m_sceneManager->createEntity("StarShipEntity", "assets/starships/starship5/starship.fbx");
    entity->getMesh()->buildTangentVectors();
    entity->setMaterialName("StarShip5_RTSS");

    auto* node = m_sceneManager->createSceneNode("StarShipNode");
    node->scale(1.5, 1.5, 1.5);
    node->rotate(Ogre::Vector3::UNIT_X, Ogre::Degree(-90));
    node->translate(0, 0, -800);
    node->attachObject(entity);

    return node;
}

Ogre::SceneNode* Environment::createAsteroids() const {
    constexpr float density = 10000;

    struct AsteroidRegion {
        Ogre::Vector3 position;
        float radius;
        float asteroidsNumber;
        float minScale;
        float maxScale;
    };

    using utils_rand = core::utils::rand;

    auto* asteroidsNode = m_sceneManager->createSceneNode("Asteroids");

    std::vector<std::string> meshes = {
        "asteroid1.fbx", "asteroid2.fbx", "asteroid3.fbx", "asteroid4.fbx", "asteroid5.fbx",
        "asteroid6.fbx", "asteroid7.fbx", "asteroid8.fbx", "asteroid9.fbx", "asteroid10.fbx"
    };
    const std::string path = "assets/asteroids/";

    std::vector<AsteroidRegion> regions = {
        { Ogre::Vector3(0, 0, 0), 100, 10, 0.01, 0.05 }
    };

    for (int i=0; i < regions.size(); i++) {
        const auto& region = regions[i];
        auto* regionNode = asteroidsNode->createChildSceneNode("region_"+std::to_string(i));

        for (int j=0; j < region.asteroidsNumber; j++) {
            auto* asteroidNode = regionNode->createChildSceneNode();

            // scale
            const float scale = utils_rand::range(region.minScale, region.maxScale);
            asteroidNode->setScale(scale, scale, scale);

            // mesh
            const std::string& mesh = meshes[utils_rand::range(0, meshes.size()-1)];
            const std::string meshPath = path+mesh;
            auto* entity = m_sceneManager->createEntity(meshPath);
            entity->setMaterialName("Asteroid_RTSS");

            asteroidNode->attachObject(entity);

            // collider
            auto shape = m_scene->physics()->tools()->getConvexHull(entity->getMesh());
            shape.shapePtr()->setLocalScaling(btVector3(scale, scale, scale));

            auto* collider = m_sceneManager->createCollider();
            collider->setShapes({ shape });
            collider->setCollisionLayer((int)CollisionLayer::Asteroid, (int)CollisionLayer::All);
            collider->setMass(scale * density);

            asteroidNode->attachObject(collider);

            // rotation
            float yaw = utils_rand::range(0.f, 2 * Ogre::Math::PI);
            float pitch = utils_rand::range(0.f, 2 * Ogre::Math::PI);
            float roll = utils_rand::range(0.f, 2 * Ogre::Math::PI);

            auto pitchQuat = Ogre::Quaternion(Ogre::Degree(pitch), Ogre::Vector3::UNIT_X);
            auto yawQuat = Ogre::Quaternion(Ogre::Degree(yaw), Ogre::Vector3::UNIT_Y);
            auto rollQuat = Ogre::Quaternion(Ogre::Degree(roll), Ogre::Vector3::UNIT_Z);

            asteroidNode->setOrientation(pitchQuat * yawQuat * rollQuat);

            // position
            float theta = utils_rand::range(0.f, 2*Ogre::Math::PI);
            float phi = utils_rand::range(-Ogre::Math::PI/2, Ogre::Math::PI/2);
            float r = std::cbrt(utils_rand::range(0.f, 1.f)) * region.radius;

            float x = r * sin(phi) * cos(theta);
            float y = r * sin(phi) * sin(theta);
            float z = r * cos(phi);

            asteroidNode->setPosition(Ogre::Vector3(x, y, z) + region.position);
        }
    }

    return asteroidsNode;
}

Ogre::SceneNode* Environment::createEarth() const {
    auto* earthEntity = m_sceneManager->createEntity("EarthEntity", "assets/earth/earth.fbx");
    earthEntity->getSubEntities()[0]->setMaterialName("EarthPlanet_RTSS");
    earthEntity->getSubEntities()[1]->setMaterialName("EarthClouds_RTSS");
    earthEntity->getSubEntities()[2]->setMaterialName("EarthAtmosphere_RTSS");

    auto* earthNode = m_sceneManager->createSceneNode("EarthNode");
    earthNode->attachObject(earthEntity);
    earthNode->setPosition(Ogre::Vector3(0, -3000, 0));
    earthNode->setScale(25, 25, 25);
    earthNode->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(90));
    earthNode->rotate(Ogre::Vector3(1, 0, 0), Ogre::Radian(-170));

    return earthNode;
}

} // end namespace game