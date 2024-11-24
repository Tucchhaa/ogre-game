#include "tools.hpp"

#include "core/objects/collider.hpp"

namespace core {

Shape PhysicsTools::getConvexHull(const Ogre::MeshPtr& mesh) {
    std::vector<btVector3> vertices;

    if (mesh->sharedVertexData) {
        extractVertices(mesh->sharedVertexData, vertices);
    }

    for (size_t i = 0; i < mesh->getNumSubMeshes(); ++i) {
        Ogre::SubMesh* subMesh = mesh->getSubMesh(i);
        Ogre::VertexData* vertexData = subMesh->vertexData;

        if(subMesh->useSharedVertices || vertexData == nullptr) {
            continue;
        }

        extractVertices(vertexData, vertices);
    }

    auto shape = std::make_shared<btConvexHullShape>(&vertices[0].getX(), vertices.size());

    shape->optimizeConvexHull();

    return Shape(shape);
}

void PhysicsTools::extractVertices(Ogre::VertexData* vertexData, std::vector<btVector3>& vertices) {
    Ogre::VertexBufferBinding* binding = vertexData->vertexBufferBinding;
    Ogre::VertexDeclaration* decl = vertexData->vertexDeclaration;
    const Ogre::VertexElement* posElem = decl->findElementBySemantic(Ogre::VES_POSITION);

    if (!posElem)
        return;

    Ogre::HardwareVertexBufferSharedPtr vbuf = binding->getBuffer(posElem->getSource());
    unsigned char* vertex = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

    for (size_t j = 0; j < vertexData->vertexCount; ++j) {
        Ogre::Vector3* pos;
        posElem->baseVertexPointerToElement(vertex, &pos);
        vertices.emplace_back(btVector3(pos->x, pos->y, pos->z));

        vertex += vbuf->getVertexSize();
    }

    vbuf->unlock();
}

} // end namespace core
