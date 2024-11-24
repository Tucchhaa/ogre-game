#include "star_fighter_controller.hpp"

#include "core/game.hpp"
#include "core/input.hpp"
#include "core/utils.hpp"
#include "core/window_manager.hpp"
#include "core/objects/collider.hpp"
#include "core/objects/transform.hpp"

namespace game {

StarFighterController::StarFighterController(const Ogre::String& name): BaseMovableObject(name)
    {}

void StarFighterController::objectAttached() {
    auto initialRotation = getParentNode()->getOrientation();
    cameraNode()->setOrientation(initialRotation);
}

inline core::CustomSceneNode* StarFighterController::cameraNode() {
    return static_cast<core::CustomSceneNode*>(core::Game::scene()->mainCamera->getParentNode());
}

void StarFighterController::update(float dt) {
    const auto input = core::Game::input();

    if(core::Game::windowManager()->relativeMouseEnabled()) {
        // Don't multiply by timeSinceLastFrame because mouseDeltaX/Y are already frame-rate independent
        float sensitivity = 5;
        const float rx = -input->mouseDeltaX() * sensitivity;
        const float ry = -input->mouseDeltaY() * sensitivity;
        const float rz = -input->deltaX() * dt * m_rollSpeed;

        cameraNode()->yaw(Ogre::Radian(rx));
        cameraNode()->pitch(Ogre::Radian(ry));
        cameraNode()->roll(Ogre::Radian(rz));
    }

    moveCamera();
    cameraNode()->transform()->resetState();
}

void StarFighterController::fixedUpdate(float dt) {
    const auto input = core::Game::input();

    m_velocity = btVector3(0, 0, 0);
    m_angularVelocity = btVector3(0, 0, 0);

    if(input->rightClick() == false) {
        moveAim(dt);
    }
    moveShip(dt);

    m_collider->rigidbody()->setLinearVelocity(m_velocity);
    m_collider->rigidbody()->setAngularVelocity(m_angularVelocity);
}

void StarFighterController::moveAim(float dt) {
    const auto rigidbody = m_collider->rigidbody();

    const auto currentQuat = rigidbody->getOrientation();
    auto targetQuat = core::utils::convertQuat(cameraNode()->getOrientation());

    if (currentQuat.dot(targetQuat) < 0.0f) {
        targetQuat = -targetQuat;
    }

    const auto deltaQuat = (targetQuat * currentQuat.inverse()).normalize();

    const auto angle = deltaQuat.getAngle();
    const auto axis = deltaQuat.getAxis();

    // auto roll = btVector3(0, 0, rz * m_rollSpeed);
    // roll = core::utils::rotateVec3(roll, rotation);

    m_angularVelocity += axis * (angle * m_angularSpeed * dt);
}

void StarFighterController::moveShip(float dt) {
    const auto input = core::Game::input();

    // velocity
    const float z = input->deltaY();
    m_speed = core::utils::clamp(m_speed + z * m_acceleration, m_minSpeed, m_maxSpeed);

    const auto movement = btVector3(0, 0, -m_speed * dt);

    const auto rotation = m_collider->rigidbody()->getOrientation();
    const auto velocity = core::utils::rotateVec3(movement, rotation);

    m_velocity += velocity;
}

void StarFighterController::moveCamera() {
    const auto* node = getCustomNode();

    const auto t = (m_speed - m_minSpeed) / (m_maxSpeed - m_minSpeed);
    const auto interpolatedBias = core::utils::lerp(t, m_cameraPosBiasMin, m_cameraPosBiasMax);
    const auto bias = cameraNode()->getOrientation() * interpolatedBias;

    const auto cameraPosition = node->getPosition() + bias;

    cameraNode()->setPosition(cameraPosition);
}

} // end namespace game
