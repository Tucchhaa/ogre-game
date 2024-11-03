/*
 * Game Development Programming mini exercise 1
 * Student ID: 112550085
 * Name: Eldar Iusupzhanov
 * Repository: https://github.com/Tucchhaa/ogre-game/tree/eldar_mini_exercise1_demo
 */

#include <iostream>

#include "core/game.hpp"
#include "core/input.hpp"
#include "core/scene.hpp"
#include "core/utils.hpp"
#include "core/window_manager.hpp"
#include "core/objects/collider.hpp"

using namespace std;

class SimpleScene : public core::Scene {
    core::CustomSceneNode* m_sphereNode = nullptr;
    core::Collider* m_sphereCollider = nullptr;

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

        createCubes();
        createGround();
        createSphere();
    }

    void update(float dt) override {
        Scene::update(dt);
        auto input = core::Game::input();

        if(input->isKeyPressed(core::Key::ESCAPE)) {
            core::Game::instance().stopRendering();
        }
        if(input->isKeyDown(core::Key::SPACE)) {
            core::Game::windowManager()->relativeMouseEnabled(
                !core::Game::windowManager()->relativeMouseEnabled()
            );
        }

        static long long lastShootTime = core::utils::getTimestamp();
        static long long reloadTime = 500;

        if(input->leftMouseClicked() && core::utils::getTimestamp() - lastShootTime >= reloadTime) {
            shootSphere();
        }
    }

    void shootSphere() {
        const auto OFFSET = Ogre::Vector3(-0.5, -0.5, 0.5);
        const float SPHERE_SPEED = 50;
        auto dir = mainCamera->getDerivedDirection();
        auto bt_dir = btVector3(dir.x, dir.y, dir.z);

        m_sphereNode->setPosition(mainCamera->getParentNode()->getPosition() + OFFSET);
        m_sphereNode->transform()->updateState();

        m_sphereCollider->resetRigidbodyTransform();
        m_sphereCollider->rigidbody()->activate(true);
        m_sphereCollider->rigidbody()->clearForces();
        m_sphereCollider->rigidbody()->setLinearVelocity(bt_dir * SPHERE_SPEED);
        m_sphereCollider->rigidbody()->setAngularVelocity(btVector3(0, 0, 0));
    }

    void createSphere() {
        const float RADIUS = 0.25;
        m_sphereNode = m_rootNode->createChildSceneNode("sphere");

        auto* entity = m_sceneManager->createEntity("sphere.obj");

        auto shape = core::Shape(make_shared<btSphereShape>(RADIUS));
        m_sphereCollider = static_cast<core::Collider*>(m_sceneManager->createMovableObject("Collider"));

        m_sphereCollider->setShapes({ shape });
        m_sphereCollider->setMass(5.0);
        m_sphereCollider->rigidbody()->setRestitution(0.5);

        m_sphereNode->scale(Ogre::Vector3(RADIUS));
        m_sphereNode->translate(Ogre::Vector3(100)); // put the sphere far away initially
        m_sphereNode->attachObject(entity);
        m_sphereNode->attachObject(m_sphereCollider);
    }

    void createCubes() {
        const int N = 5;
        const float CUBE_SCALE = 1.0f;
        const auto CUBES_OFFSET = Ogre::Vector3(0, 5, 0);
        auto* cubesNode = m_rootNode->createChildSceneNode("cubes", CUBES_OFFSET);

        for(int i=0; i < N; i++) {
            for(int j=0; j < N; j++) {
                for(int k=0; k < N; k++) {
                    auto position = Ogre::Vector3(i, j, k) * CUBE_SCALE;
                    auto* cube = m_sceneManager->createEntity("cube.obj");

                    auto* node = cubesNode->createChildSceneNode();
                    node->translate(position);
                    node->scale(Ogre::Vector3(CUBE_SCALE));
                    node->attachObject(cube);

                    auto shape = core::Shape(make_shared<btBoxShape>(btVector3(CUBE_SCALE, CUBE_SCALE, CUBE_SCALE)));
                    auto* collider = static_cast<core::Collider*>(m_sceneManager->createMovableObject("Collider"));
                    collider->setShapes({ shape });
                    node->attachObject(collider);
                }
            }
        }
    }

    void createGround() {
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
};

int main()
{
    const auto scene = make_shared<SimpleScene>();

    auto& game = core::Game::instance();
    // game.debugMode(true);
    game.configure();
    game.init();
    game.scene(scene);

    game.startNetwork();
    game.startRendering();

    return 0;
}