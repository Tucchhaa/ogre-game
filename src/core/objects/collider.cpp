#include "collider.hpp"

#include "../game.hpp"
#include "../physics_world.hpp"

namespace core {

Collider::Collider(const Ogre::String& name): BaseMovableObject(name) { }

void Collider::setShapes(const vector<Shape>& shapes) {
    m_shapes = shapes;
    m_shape = createCompoundShape();
    m_rigidBody = createRigidBody();
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
    const auto nodePosition = &getParentNode()->getPosition();
    const auto nodeRotation = &getParentNode()->getOrientation();

    btTransform transform;

    transform.setOrigin(btVector3(nodePosition->x, nodePosition->y, nodePosition->z));
    transform.setRotation(btQuaternion(nodeRotation->x, nodeRotation->y, nodeRotation->z, nodeRotation->w));

    if (m_rigidBody && m_rigidBody->getMotionState()) {
        m_rigidBody->getMotionState()->setWorldTransform(transform);
    }

    m_rigidBody->setWorldTransform(transform);
}

void Collider::updateSceneNodeTransform() const {
    btTransform colliderTransform;

    if (m_rigidBody && m_rigidBody->getMotionState()) {
        m_rigidBody->getMotionState()->getWorldTransform(colliderTransform);
    }
    else {
        colliderTransform = m_rigidBody->getWorldTransform();
    }

    const auto& position = colliderTransform.getOrigin();
    const auto& rotation = colliderTransform.getRotation();

    getParentNode()->setPosition(Ogre::Vector3(position.x(), position.y(), position.z()));
    getParentNode()->setOrientation(Ogre::Quaternion(rotation.w(), rotation.x(), rotation.y(), rotation.z()));
}

void Collider::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    if(getParentNode() != nullptr) {
        updateSceneNodeTransform();
    }
}

void Collider::objectAttached() {
    resetRigidbodyTransform();

    Game::physics()->addRigidBody(m_rigidBody);
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
    auto rigidBody = make_shared<btRigidBody>(info);

    return rigidBody;
}

} // end namespace core
