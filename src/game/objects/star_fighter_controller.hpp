#pragma once

#include <LinearMath/btVector3.h>

#include "core/objects/base_movable_object.hpp"

namespace core {

class Collider;
class CustomSceneNode;

}

namespace game {

const Ogre::String STAR_FIGHTER_CONTROLLER_TYPE = "StarFighterController";

class StarFighterController : public core::BaseMovableObject {
public:
    using Vec3 = Ogre::Vector3;
    using Quat = Ogre::Quaternion;

    StarFighterController() = default;
    explicit StarFighterController(const Ogre::String& name);

    const Ogre::String& getMovableType() const override { return STAR_FIGHTER_CONTROLLER_TYPE; }

    void setCollider(core::Collider* collider) { m_collider = collider; }

    void objectAttached() override;

    /// Velocity of the star fighter. Note: use only in logic thread
    const btVector3& velocity() const {return m_velocity; }

private:
    const float m_minSpeed = 0;
    // const float m_minSpeed = 1000.0;
    const float m_maxSpeed = 10000.0;
    std::atomic<float> m_speed = m_minSpeed;

    const float m_acceleration = 100;
    const float m_angularSpeed = 600.0;
    const float m_rollSpeed = 2.5;

    const Ogre::Vector3 m_cameraBiasMin = Ogre::Vector3(0, 6, 25);
    const Ogre::Vector3 m_cameraBiasMax = Ogre::Vector3(0, 9, 35);
    const Ogre::Vector3 m_cameraRollBiasMax = Ogre::Vector3(5, 0, 0);
    Ogre::Vector3 m_cameraRollBias = Ogre::Vector3::ZERO;
    const float m_cameraRollBiasLerpFactor = 3;

    core::Collider* m_collider = nullptr;
    btVector3 m_velocity = btVector3(0, 0, 0);
    btVector3 m_angularVelocity = btVector3(0, 0, 0);

    static inline core::CustomSceneNode* cameraNode();

    void update(float dt) override;

    void fixedUpdate(float dt) override;

    void moveAim(float dt);

    void moveShip(float dt);

    void moveCamera();
};

class StarFighterControllerFactory : public Ogre::MovableObjectFactory {
    Ogre::MovableObject* createInstanceImpl(const Ogre::String& name, const Ogre::NameValuePairList* params) override {
        return new StarFighterController(name);
    }

public:
    const Ogre::String& getType() const override { return STAR_FIGHTER_CONTROLLER_TYPE; };
};

} // end namespace game
