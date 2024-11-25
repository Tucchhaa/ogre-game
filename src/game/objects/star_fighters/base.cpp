#include "base.hpp"

#include "core/game.hpp"
#include "core/objects/collider.hpp"
#include "core/physics/tools.hpp"
#include "game/objects/star_fighter_controller.hpp"

game::BaseStarFighter::BaseStarFighter(const std::string& model): ID(generateID()) {
    const auto scene = core::Game::scene();
    const auto sceneManager = scene->sceneManager();

    const std::string convexHullFile = "assets/star_fighters/convex/StarFighterConvex1.obj";
    const std::string modelFile = "assets/star_fighters/"+model;

    const std::string wrapperNodeName = "ShipNodeWrapper_"+std::to_string(ID);
    const std::string shipNodeName    = "ShipNode_"+std::to_string(ID);

    m_node = scene->root()->createChildSceneNode(wrapperNodeName);

    // collider
    auto colliderMesh = core::Game::meshManager()->load(convexHullFile, "General");
    auto shape = scene->physics()->tools()->getConvexHull(colliderMesh);
    shape.transform()->setRotation(btQuaternion(btVector3(0, 1, 0), SIMD_PI));

    auto* colliderObj = sceneManager->createMovableObject("Collider");
    auto* collider = static_cast<core::Collider*>(colliderObj);
    collider->setShapes({ shape });
    collider->rigidbody()->setActivationState(DISABLE_DEACTIVATION);

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

    auto* shipNode = m_node->createChildSceneNode(shipNodeName);
    shipNode->scale(0.01, 0.01, 0.01);
    shipNode->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(180));
    shipNode->attachObject(shipEntity);
}
