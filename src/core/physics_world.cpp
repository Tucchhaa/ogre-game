#include "physics_world.hpp"

namespace core {

PhysicsWorld::PhysicsWorld() {
    m_collisionConfiguration = make_unique<btDefaultCollisionConfiguration>();
    m_dispatcher             = make_unique<btCollisionDispatcher>(m_collisionConfiguration.get());
    m_overlappingPairCache   = make_unique<btDbvtBroadphase>();
    m_solver                 = make_unique<btSequentialImpulseConstraintSolver>();
    m_dynamicsWorld            = make_unique<btDiscreteDynamicsWorld>(
        m_dispatcher.get(), m_overlappingPairCache.get(),
        m_solver.get(), m_collisionConfiguration.get()
    );

    m_dynamicsWorld->setGravity(gravity);
}

void PhysicsWorld::addRigidBody(const shared_ptr<btRigidBody>& rigidBody) const {
    m_dynamicsWorld->addRigidBody(rigidBody.get());
}

void PhysicsWorld::removeRigidBody(const shared_ptr<btRigidBody>& rigidBody) const {
    m_dynamicsWorld->removeRigidBody(rigidBody.get());
}

void PhysicsWorld::stepSimulation(float dt) const {
    m_dynamicsWorld->stepSimulation(dt); // TODO: make simulation step every constant seconds
}

} // end namespace core
