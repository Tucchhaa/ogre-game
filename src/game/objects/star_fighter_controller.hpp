#pragma once

#include "../../../vcpkg/buildtrees/bullet3/src/3.25-98f155ca90.clean/src/LinearMath/btVector3.h"
#include "core/objects/base_movable_object.hpp"

class btVector3;

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

private:
    float m_minSpeed = 1000.0;
    float m_maxSpeed = 10000.0;
    float m_speed = m_minSpeed;

    float m_acceleration = 100;
    float m_angularSpeed = 100.0;
    float m_rollSpeed = 2.5;

    Ogre::Vector3 m_cameraPosBiasMin = Ogre::Vector3(0, 6, 25);
    Ogre::Vector3 m_cameraPosBiasMax = Ogre::Vector3(0, 9, 35);

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
