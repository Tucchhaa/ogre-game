#include "fighter.hpp"

#include "core/game.hpp"
#include "core/utils.hpp"
#include "core/objects/collider.hpp"
#include "core/objects/transform.hpp"
#include "game/galactic_wars_game.hpp"
#include "game/objects/star_fighter_controller.hpp"
#include "game/scenes/space_scene/scene.hpp"
#include "game/ui/fighter_indicators.hpp"

namespace game {

Fighter::Fighter(): BaseStarFighter("StarFighter01.fbx") {
    m_bullets.resize(m_maxAmmo);

    m_lastPrimaryReloadTimestamp = core::utils::getTimestamp();
    m_lastPrimaryAttackTimestamp = core::utils::getTimestamp();

    auto* bulletsContainerNode = m_wrapperNode->createChildSceneNode("Bullets_"+std::to_string(ID));

    for (int i=0; i < m_ammo; i++) {
        auto* bulletNode = bulletsContainerNode->createChildSceneNode();
        auto* entity = core::Game::sceneManager()->createEntity("base_shapes/cylinder.fbx");
        entity->setMaterialName("Bullet");

        bulletNode->attachObject(entity);
        bulletNode->setVisible(false);

        auto shape = core::Shape(std::make_shared<btSphereShape>(0.15));
        auto collisionLayer = (int)CollisionLayer::Asteroid | (int)CollisionLayer::StarFighter | (int)CollisionLayer::StarShip;
        auto* collider = core::Game::sceneManager()->createCollider();

        collider->setShapes({ shape });
        collider->setMass(m_bulletMass);
        collider->setCollisionLayer((int)CollisionLayer::Bullet, collisionLayer);

        // TODO: it's not very effective, because the callback is called even when bullet doesn't collide with anything
        collider->setOnCollide([bulletNode](core::Collider* self, const btCollisionObject* other) {
            self->rigidbody()->setActivationState(ISLAND_SLEEPING);
            self->rigidbody()->clearForces();
            self->rigidbody()->setLinearVelocity(btVector3(0, 0, 0));
            self->rigidbody()->setAngularVelocity(btVector3(0, 0, 0));
            bulletNode->setVisible(false);
        });

        collider->rigidbody()->setAngularFactor(btVector3(0, 0, 0));
        collider->rigidbody()->setActivationState(ISLAND_SLEEPING);

        bulletNode->attachObject(collider);
        bulletNode->setScale(0.0017, 0.0017, 0.005);

        m_bullets[i] = { bulletNode, collider };
    }
}

void Fighter::primaryAttack(float dt) {
    if (m_ammo < m_ammoPerShoot)
        return;

    const auto now = core::Game::currentUpdateTimestamp();

    if (now - m_lastPrimaryAttackTimestamp < m_delayPerShoot) {
        return;
    }

    m_bulletIndex = (m_bulletIndex + m_ammoPerShoot) % m_maxAmmo;
    m_ammo -= m_ammoPerShoot;
    m_lastPrimaryAttackTimestamp = now;
    m_lastPrimaryReloadTimestamp = now; // to start reloading only after shooting stopped

    for (int i=0; i < m_ammoPerShoot; i++) {
        auto* node = m_bullets[m_bulletIndex + i].node;
        auto* collider = m_bullets[m_bulletIndex + i].collider;
        auto shootingPos = m_shootingPositions[i];
        node->setVisible(true);

        const auto rotation = m_node->getOrientation();
        const auto position = m_node->getPosition() + rotation * shootingPos;

        node->setPosition(position);
        node->setOrientation(rotation);
        node->transform()->resetState();

        const auto btRotation = core::utils::convertQuat(rotation);
        const auto velocity = core::utils::rotateVec3(btVector3(0, 0, -m_bulletSpeed), btRotation);

        collider->resetRigidbodyTransform();
        collider->rigidbody()->setActivationState(ACTIVE_TAG);
        collider->rigidbody()->setLinearVelocity(velocity + m_controller->velocity());
    }
}

void Fighter::secondaryAttack(float dt) {
}

void Fighter::fixedUpdate(float dt) {
    BaseStarFighter::fixedUpdate(dt);

    const auto now = core::Game::currentUpdateTimestamp();
    const auto supplyAmmo = (int)(now - m_lastPrimaryReloadTimestamp) / m_delayPerReload;

    // reload when not shooting
    if (supplyAmmo > 0) {
        m_ammo += supplyAmmo;
        m_ammo = std::min(m_ammo, m_maxAmmo);

        m_lastPrimaryReloadTimestamp = now;
    }

    m_indicators->updateAmmoIndicators(m_ammo, m_maxAmmo);
}

} // game