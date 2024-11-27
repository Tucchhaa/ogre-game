#include "base.hpp"

#include "core/game.hpp"
#include "core/input.hpp"
#include "core/window_manager.hpp"
#include "core/objects/collider.hpp"
#include "core/physics/tools.hpp"
#include "game/galactic_wars_game.hpp"
#include "game/objects/star_fighter_controller.hpp"

namespace game {

BaseStarFighter::BaseStarFighter(const std::string& model): ID(generateID()) {
    const auto scene = core::Game::scene();
    const auto sceneManager = scene->sceneManager();

    const std::string convexHullFile = "assets/star_fighters/convex/StarFighterConvex1.obj";
    const std::string modelFile      = "assets/star_fighters/"+model;

    const std::string wrapperNodeName = "StarFighterWrapper_"+std::to_string(ID);
    const std::string nodeName        = "StarFighterNode_"+std::to_string(ID);
    const std::string meshNodeName    = "StarFighterMesh_"+std::to_string(ID);

    m_wrapperNode = scene->root()->createChildSceneNode(wrapperNodeName);
    m_node = m_wrapperNode->createChildSceneNode(nodeName);

    auto* collider = createCollider(convexHullFile);
    m_node->attachObject(collider);

    // controller
    m_controller = static_cast<StarFighterController*>(
        sceneManager->createMovableObject("StarFighterController")
    );
    m_controller->setCollider(collider);

    m_node->attachObject(m_controller);

    // entity
    auto* shipEntity = sceneManager->createEntity(modelFile);
    // TODO: Check if it's better to remove building tangents at runtime
    shipEntity->getMesh()->buildTangentVectors();
    shipEntity->setMaterialName("StarFighter_RTSS");

    auto* meshNode = m_node->createChildSceneNode(meshNodeName);
    meshNode->scale(0.01, 0.01, 0.01);
    meshNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(180));
    meshNode->attachObject(shipEntity);
}

void BaseStarFighter::fixedUpdate(float dt) {
    if(!core::Game::windowManager()->relativeMouseEnabled()) {
        return;
    }

    if (core::Game::input()->leftClick()) {
        primaryAttack(dt);
    }

    // if (core::Game::input()->rightClick()) {
    //     secondaryAttack(dt);
    // }
}

core::Collider* BaseStarFighter::createCollider(const std::string& convexHullFile) {
    const auto meshManager = core::Game::meshManager();
    const auto sceneManager = core::Game::sceneManager();
    const auto scene = core::Game::scene();

    auto convexMesh = meshManager->load(convexHullFile, "General");
    auto shape = scene->physics()->tools()->getConvexHull(convexMesh);

    shape.transform()->setRotation(btQuaternion(btVector3(0, 1, 0), SIMD_PI));

    auto* collider = sceneManager->createCollider();

    collider->setShapes({ shape });
    collider->setCollisionLayer((int)CollisionLayer::StarFighter, (int)CollisionLayer::All);
    collider->rigidbody()->setActivationState(DISABLE_DEACTIVATION);

    return collider;
}

} // end namespace game
