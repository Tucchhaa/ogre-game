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
    using callback_type = std::function<void(Collider* self, const btCollisionObject* other)>;

    Collider() = default;
    explicit Collider(const Ogre::String& name): BaseMovableObject(name) {}

    const Ogre::String& getMovableType() const override { return COLLIDER_TYPE; }

    /// Returns btRigidbody. Must be accessed only in logic thread (aka fixedUpdate)
    std::shared_ptr<btRigidBody> rigidbody() const { return m_rigidBody; }

    /**
     * Sets shapes of the collider.
     * Note: call this method only once.
     */
    void setShapes(const std::vector<Shape> &shapes);

    /// Configure which collider groups can collide with this collider
    /// @param group which group this collider belong to
    /// @param mask which groups can collide with this collider
    void setCollisionLayer(int group, int mask);

    /**
     * Sets mass of the collider. If mass is 0, the collider is fixed in space.
     */
    void setMass(float mass);

    /**
     * Returns true if the collider is dynamic (not fixed in space)
     */
    bool isDynamic() const;

    void setOnCollide(const callback_type& callback) { m_onCollideCallback = callback; }

    /**
     * Resets rigid body transform to parent scene node's transform.
     * Call it after Ogre::SceneNode transform was changed to update rigid body's state
     */
    void resetRigidbodyTransform() const;

    void onCollide(const btCollisionObject* other);

protected:
    void objectAttached() override;

private:
    std::shared_ptr<btCompoundShape> m_shape;
    std::vector<Shape> m_shapes;
    std::shared_ptr<btRigidBody> m_rigidBody;
    callback_type m_onCollideCallback;

    int m_mask = 0;
    int m_group = 0;
    float m_mass = 1.;

    void sceneInited() override;

    void fixedUpdate(float dt) override;

    void update(float dt) override;

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
