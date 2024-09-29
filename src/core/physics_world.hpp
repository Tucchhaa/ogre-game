#pragma once

#include <memory>
#include "bullet/btBulletDynamicsCommon.h"

using namespace std;

namespace core {
class PhysicsWorld {
public:
    PhysicsWorld();

    /**
     * Add rigidbody to physics simulation
     */
    void addRigidBody(const shared_ptr<btRigidBody>& rigidBody) const;

    /**
     * Remove rigidbody from physics simulation
     */
    void removeRigidBody(const shared_ptr<btRigidBody>& rigidBody) const;

    /**
     * Step physics simulation by delta time (seconds)
     */
    void stepSimulation(float dt) const;

private:
    unique_ptr<btDynamicsWorld> m_dynamicsWorld;

    unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;

    unique_ptr<btCollisionDispatcher> m_dispatcher;

    unique_ptr<btBroadphaseInterface> m_overlappingPairCache;

    unique_ptr<btSequentialImpulseConstraintSolver> m_solver;

    btVector3 gravity = btVector3(0, -10, 0);

    btAlignedObjectArray<shared_ptr<btCollisionShape>> collisionShapes;
};

} // end namespace core