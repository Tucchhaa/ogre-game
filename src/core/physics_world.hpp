#pragma once

#include <memory>
#include <bullet/btBulletDynamicsCommon.h>

#include "collider_drawer.hpp"

using namespace std;

namespace core {
class PhysicsWorld {
public:
    PhysicsWorld();

    ~PhysicsWorld();

    /**
     * Add rigidbody to physics simulation
     */
    void addRigidBody(const shared_ptr<btRigidBody>& rigidBody) const;

    /**
     * Remove rigidbody from physics simulation
     */
    void removeRigidBody(const shared_ptr<btRigidBody>& rigidBody) const;

    /**
     * Step physics simulation by delta time (seconds).
     * Note: Use when simulate physics on each frame
     */
    void stepSimulation(float dt) const;

    /**
     * Step physics simulation by constant delta time.
     * Note: use when simulate physics in a logic thread
     * @param dt delta time
     */
    void stepSimulationFixed(float dt) const;

    void drawColliders() const;

private:
    unique_ptr<btDynamicsWorld> m_dynamicsWorld;

    unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;

    unique_ptr<btCollisionDispatcher> m_dispatcher;

    unique_ptr<btBroadphaseInterface> m_overlappingPairCache;

    unique_ptr<btSequentialImpulseConstraintSolver> m_solver;

    btVector3 m_gravity = btVector3(0, -10, 0);

    btAlignedObjectArray<shared_ptr<btCollisionShape>> m_collisionShapes;

    unique_ptr<debug::ColliderDrawer> m_colliderDrawer;
};

} // end namespace core