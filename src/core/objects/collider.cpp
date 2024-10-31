#include "collider.hpp"

#include "../game.hpp"
#include "../physics_world.hpp"
#include "../utils.hpp"

using namespace std;

namespace core {

void ColliderState::setValues(const btVector3& position, const btQuaternion& rotation) {
    unique_lock _(m_mutex);

    // use unsafe functions because mutex is already locked
    set_position_unsafe(utils::convertVec3(position));
    set_rotation_unsafe(utils::convertQuat(rotation));
}

void ColliderState::getValues(Ogre::Vector3& position, Ogre::Quaternion& rotation) {
    shared_lock _(m_mutex);

    // use unsafe functions because mutex is already locked
    position = interpolate_position_unsafe();
    rotation = interpolate_rotation_unsafe();
}

void ColliderState::resetValues(const btVector3& position, const btQuaternion& rotation) {
    unique_lock _(m_mutex);

    m_position = m_previous_position = utils::convertVec3(position);
    m_rotation = m_previous_rotation = utils::convertQuat(rotation);
}

void ColliderState::serialize(std::ostream& stream) {
    shared_lock _(m_mutex);

    STREAM_WRITE(stream, m_position);
    STREAM_WRITE(stream, m_rotation);
}

void ColliderState::deserialize(std::istream& stream) {
    Ogre::Vector3 position;
    Ogre::Quaternion rotation;

    STREAM_READ(stream, position);
    STREAM_READ(stream, rotation);

    unique_lock _(m_mutex);

    // use unsafe functions because mutex is already locked
    set_position_unsafe(position);
    set_rotation_unsafe(rotation);
}

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
    const auto nodePosition = &getParentNode()->_getDerivedPosition();
    const auto nodeRotation = &getParentNode()->_getDerivedOrientation();
    btTransform transform;

    transform.setOrigin(btVector3(nodePosition->x, nodePosition->y, nodePosition->z));
    transform.setRotation(btQuaternion(nodeRotation->x, nodeRotation->y, nodeRotation->z, nodeRotation->w));

    if (m_rigidBody && m_rigidBody->getMotionState()) {
        m_rigidBody->getMotionState()->setWorldTransform(transform);
    }

    m_rigidBody->setWorldTransform(transform);
    m_state->resetValues(transform.getOrigin(), transform.getRotation());
}

void Collider::updateSceneNodeTransform() const {
    Ogre::Vector3 position;
    Ogre::Quaternion rotation;

    m_state->getValues(position, rotation);

    getParentNode()->_setDerivedPosition(position);
    getParentNode()->_setDerivedOrientation(rotation);
}

void Collider::fixedUpdate(float dt) {
    auto transform = getTransform();

    m_state->setValues(transform.getOrigin(), transform.getRotation());
}

void Collider::update(float dt) {
    if(getParentNode() != nullptr) {
        updateSceneNodeTransform();
    }
}

void Collider::objectAttached() {
    BaseMovableObject::objectAttached();

    resetRigidbodyTransform();

    Game::physics()->addRigidBody(m_rigidBody);
}

btTransform Collider::getTransform() const {
    btTransform colliderTransform;

    if (m_rigidBody && m_rigidBody->getMotionState()) {
        m_rigidBody->getMotionState()->getWorldTransform(colliderTransform);
    }
    else {
        colliderTransform = m_rigidBody->getWorldTransform();
    }

    return colliderTransform;
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
