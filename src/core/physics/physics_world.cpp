#include "physics_world.hpp"

#include <unordered_set>
#include "tools.hpp"
#include "core/objects/collider.hpp"

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
    m_tools = make_unique<PhysicsTools>();
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

void PhysicsWorld::addRigidbody(const shared_ptr<btRigidBody>& rigidbody, int group, int mask) const {
    if (group <= 0 || mask <= 0) {
        m_dynamicsWorld->addRigidBody(rigidbody.get());
    }
    else {
        m_dynamicsWorld->addRigidBody(rigidbody.get(), group, mask);
    }
}

void PhysicsWorld::removeRigidbody(const shared_ptr<btRigidBody>& rigidbody) const {
    m_dynamicsWorld->removeRigidBody(rigidbody.get());
}

void PhysicsWorld::stepSimulation(float dt) const {
    m_dynamicsWorld->stepSimulation(dt);
}

void PhysicsWorld::stepSimulationFixed(float dt) const {
    m_dynamicsWorld->stepSimulation(dt, 0);

    processCollisions();
}

void PhysicsWorld::drawColliders() const {
    m_dynamicsWorld->debugDrawWorld();
    m_colliderDrawer->render();
}

void PhysicsWorld::processCollisions() const {
    int numManifolds = m_dispatcher->getNumManifolds();
    unordered_map<const btCollisionObject*, vector<const btCollisionObject*>> collisions;

    for (int i = 0; i < numManifolds; i++) {
        auto* manifold = m_dispatcher->getManifoldByIndexInternal(i);

        auto* objA = manifold->getBody0();
        auto* objB = manifold->getBody1();

        int numContacts = manifold->getNumContacts();

        for (int j = 0; j < numContacts; j++) {
            btManifoldPoint& pt = manifold->getContactPoint(j);

            if (pt.getDistance() < 0.f) {
                collisions[objA].push_back(objB);
                collisions[objB].push_back(objA);
                break;
            }
        }
    }

    for (const auto& collision : collisions) {
        auto* collider = static_cast<Collider*>(collision.first->getUserPointer());

        for (const auto* other : collision.second) {
            collider->onCollide(other);
        }
    }
}

} // end namespace core
