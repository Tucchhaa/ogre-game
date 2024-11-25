#pragma once

#include <btBulletCollisionCommon.h>
#include <Ogre.h>

namespace core {

class Shape;

class PhysicsTools {
public:
    Shape getConvexHull(const Ogre::MeshPtr& mesh);

private:
    void extractVertices(Ogre::VertexData* vertexData, std::vector<btVector3>& vertices);
};

} // end namespace core

