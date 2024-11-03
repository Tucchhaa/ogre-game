#pragma once

#include <vector>
#include <btBulletDynamicsCommon.h>

#include "base_movable_object.hpp"

namespace core {

/**
 * Shape is building block of a collider.
 * Shape consists of a shape mesh and a transform that's relative to the collider they
 * are attached to, and the shape mesh.
 */
class Shape {
public:
    explicit Shape(
        const std::shared_ptr<btCollisionShape>& shape,
        const btTransform& transform = btTransform::getIdentity()
    ): m_btShape(shape), m_btTransform(transform) {}

    btCollisionShape* shapePtr() const { return m_btShape.get(); }

    btTransform transform() const { return m_btTransform; }
    btTransform* transform() { return &m_btTransform; }

private:
    std::shared_ptr<btCollisionShape> m_btShape;
    btTransform m_btTransform;
};

const Ogre::String COLLIDER_TYPE = "Collider";

/**
 * Collider is a component that adds physics to a game object.
 */
class Collider : public BaseMovableObject {
public:
    Collider() = default;
    explicit Collider(const Ogre::String& name): BaseMovableObject(name) {}

    const Ogre::String& getMovableType() const override { return COLLIDER_TYPE; }
    std::shared_ptr<btRigidBody> rigidbody() const { return m_rigidBody; }

    void start() override;

    void fixedUpdate(float dt) override;

    /**
     * Sets shapes of the collider.
     * Note: call this method only once.
     */
    void setShapes(const std::vector<Shape> &shapes);

    /**
     * Sets mass of the collider. If mass is 0, the collider is fixed in space.
     */
    void setMass(float mass);

    /**
     * Returns true if the collider is dynamic (not fixed in space)
     */
    bool isDynamic() const;

protected:
    void objectAttached() override;

private:
    std::shared_ptr<btCompoundShape> m_shape;
    std::vector<Shape> m_shapes;
    std::shared_ptr<btRigidBody> m_rigidBody;
    float m_mass = 1.;

    /**
     * Update SceneNode's transfrom from rigidbody's transform
     */
    void updateTransform() const;

    /**
     * Resets rigid body transform to parent scene node's transform.
     * Call it after Ogre::SceneNode transform was changed to update rigid body's state
     */
    void resetRigidbodyTransform() const;

    std::shared_ptr<btCompoundShape> createCompoundShape() const;

    std::shared_ptr<btRigidBody> createRigidBody() const;

    btTransform getRigidbodyTransform() const;
};

class ColliderFactory : public Ogre::MovableObjectFactory {
    Ogre::MovableObject* createInstanceImpl(const Ogre::String& name, const Ogre::NameValuePairList* params) override {
        return new Collider(name);
    }

public:
    const Ogre::String& getType() const override { return COLLIDER_TYPE; };
};

} // end namespace core
