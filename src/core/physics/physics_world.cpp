#include "physics_world.hpp"

using namespace std;

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
    m_colliderDrawer = make_unique<debug::ColliderDrawer>();

    m_dynamicsWorld->setGravity(m_gravity);
    m_dynamicsWorld->setDebugDrawer(m_colliderDrawer.get());
}

PhysicsWorld::~PhysicsWorld() {
    for (int i = 0; i < m_dynamicsWorld->getNumCollisionObjects(); i++) {
        btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);

        if (body && body->getMotionState())
            delete body->getMotionState();

        m_dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }

    for (int j = 0; j < m_collisionShapes.size(); j++)
        m_collisionShapes[j].reset();

    m_dynamicsWorld.reset();
    m_solver.reset();
    m_overlappingPairCache.reset();
    m_dispatcher.reset();
    m_collisionConfiguration.reset();

    m_collisionShapes.clear();
}

void PhysicsWorld::addRigidBody(const shared_ptr<btRigidBody>& rigidBody) const {
    m_dynamicsWorld->addRigidBody(rigidBody.get());
}

void PhysicsWorld::removeRigidBody(const shared_ptr<btRigidBody>& rigidBody) const {
    m_dynamicsWorld->removeRigidBody(rigidBody.get());
}

void PhysicsWorld::stepSimulation(float dt) const {
    m_dynamicsWorld->stepSimulation(dt);
}

void PhysicsWorld::stepSimulationFixed(float dt) const {
    m_dynamicsWorld->stepSimulation(dt, 0);
}

void PhysicsWorld::drawColliders() const {
    m_dynamicsWorld->debugDrawWorld();
    m_colliderDrawer->render();
}
} // end namespace core
