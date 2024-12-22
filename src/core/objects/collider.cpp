#include "collider.hpp"

#include <iostream>

#include "transform.hpp"
#include "../game.hpp"
#include "../physics/physics_world.hpp"

using namespace std;

namespace core {

void Collider::sceneInited() {
    resetRigidbodyTransform();
}

void Collider::fixedUpdate(float dt) {
    auto rigidbodyTransform = getRigidbodyTransform();

    transformState()->setValues(
        rigidbodyTransform.getOrigin(),
        rigidbodyTransform.getRotation()
    );
}

void Collider::update(float dt) {
    getCustomNode()->transform()->updateNodeTransform();
}

void Collider::onCollide(const btCollisionObject* other) {
    if (m_onCollideCallback) {
        m_onCollideCallback(this, other);
    }
}

void Collider::setShapes(const vector<Shape>& shapes) {
    m_shapes = shapes;
    m_shape = createCompoundShape();
    m_rigidBody = createRigidBody();

    m_rigidBody->setUserPointer(this);
}

void Collider::setCollisionLayer(int group, int mask) {
    m_group = group;
    m_mask = mask;
}

void Collider::setMass(float mass) {
    this->m_mass = mass;
    btVector3 inertia(0, 0, 0);

    if(mass != 0.f) {
        m_rigidBody->getCollisionShape()->calculateLocalInertia(mass, inertia);
    }

    m_rigidBody->setMassProps(mass, inertia);

    m_rigidBody->updateInertiaTensor();
    m_rigidBody->activate();
}

bool Collider::isDynamic() const {
    return m_mass != 0.f;
}

void Collider::resetRigidbodyTransform() const {
    btVector3 position;
    btQuaternion rotation;
    btTransform transform;

    transformState()->getValues(position, rotation);
    transform.setOrigin(position);
    transform.setRotation(rotation);

    if (m_rigidBody && m_rigidBody->getMotionState()) {
        m_rigidBody->getMotionState()->setWorldTransform(transform);
    }

    m_rigidBody->setWorldTransform(transform);
}

void Collider::objectAttached() {
    Game::physics()->addRigidbody(m_rigidBody, m_group, m_mask);
}

btTransform Collider::getRigidbodyTransform() const {
    btTransform rigidbodyTransform;

    if (m_rigidBody && m_rigidBody->getMotionState()) {
        m_rigidBody->getMotionState()->getWorldTransform(rigidbodyTransform);
    }
    else {
        rigidbodyTransform = m_rigidBody->getWorldTransform();
    }

    return rigidbodyTransform;
}

shared_ptr<btCompoundShape> Collider::createCompoundShape() const {
    auto compoundShape = make_shared<btCompoundShape>();

    for(const auto& shape: m_shapes) {
        compoundShape->addChildShape(shape.transform(), shape.shapePtr());
    }

    return compoundShape;
}

shared_ptr<btRigidBody> Collider::createRigidBody() const {
    btVector3 localInertia(0, 0, 0);

    if (isDynamic()) {
        m_shape->calculateLocalInertia(m_mass, localInertia);
    }

    auto* motionState = new btDefaultMotionState(btTransform::getIdentity());
    auto info = btRigidBody::btRigidBodyConstructionInfo(m_mass, motionState, m_shape.get(), localInertia);
    auto rigidbody = make_shared<btRigidBody>(info);

    return rigidbody;
}

} // end namespace core
