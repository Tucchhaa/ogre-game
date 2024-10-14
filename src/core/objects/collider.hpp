#pragma once

#include <vector>
#include <btBulletDynamicsCommon.h>

#include "base_movable_object.hpp"

using namespace std;

namespace core {

/**
 * Shape is building block of a collider.
 * Shape consists of a shape mesh and a transform that's relative to the collider they
 * are attached to, and the shape mesh.
 */
class Shape {
public:
    explicit Shape(
        const shared_ptr<btCollisionShape>& shape,
        const btTransform& transform = btTransform::getIdentity()
    ): m_btShape(shape), m_btTransform(transform) {}

    btCollisionShape* shapePtr() const { return m_btShape.get(); }

    btTransform transform() const { return m_btTransform; }
    btTransform* transform() { return &m_btTransform; }

private:
    shared_ptr<btCollisionShape> m_btShape;
    btTransform m_btTransform;
};

/**
 * Synchronizes colliders position and rotation between render and logic threads
 */
class ColliderState: public State {
    STATE_INTERPOLATABLE_PROP(Ogre::Vector3, position);
    STATE_INTERPOLATABLE_PROP(Ogre::Quaternion, rotation);

public:
    void setValues(const btVector3& position, const btQuaternion& rotation);

    void getValues(Ogre::Vector3& position, Ogre::Quaternion& rotation);
};

const Ogre::String COLLIDER_TYPE = "Collider";

/**
 * Collider is a component that adds physics to a game object.
 */
class Collider : public BaseMovableObject {
public:
    Collider() = default;
    explicit Collider(const Ogre::String& name);

    const Ogre::String& getMovableType() const override { return COLLIDER_TYPE; }
    shared_ptr<btRigidBody> rigidbody() const { return m_rigidBody; }
    shared_ptr<State> state() override { return static_pointer_cast<State>(m_state); }

    void fixedUpdate(float dt) override;

    void update(float dt) override;

    /**
     * Sets shapes of the collider.
     * Note: call this method only once.
     */
    void setShapes(const vector<Shape> &shapes);

    /**
     * Sets mass of the collider. If mass is 0, the collider is fixed in space.
     */
    void setMass(float mass);

    /**
     * Returns true if the collider is dynamic (not fixed in space)
     */
    bool isDynamic() const;

    /**
     * Resets rigid body transform to parent scene node's transform
     */
    void resetRigidbodyTransform() const;

    /**
     * Updates parent scene node's transform from rigid body transform
     */
    void updateSceneNodeTransform() const;

protected:
    void objectAttached() override;

    btTransform getTransform() const;

private:
    shared_ptr<ColliderState> m_state = make_shared<ColliderState>();
    shared_ptr<btCompoundShape> m_shape;
    vector<Shape> m_shapes;
    shared_ptr<btRigidBody> m_rigidBody;
    float m_mass = 1.;

    shared_ptr<btCompoundShape> createCompoundShape() const;

    shared_ptr<btRigidBody> createRigidBody() const;
};

class ColliderFactory : public Ogre::MovableObjectFactory {
    Ogre::MovableObject* createInstanceImpl(const Ogre::String& name, const Ogre::NameValuePairList* params) override {
        return new Collider(name);
    }

public:
    const Ogre::String& getType() const override { return COLLIDER_TYPE; };
};

} // end namespace core
