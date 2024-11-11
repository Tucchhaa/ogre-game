#include "collider_drawer.hpp"

#include "../game.hpp"

namespace core {

debug::ColliderDrawer::ColliderDrawer() {
    m_material = createMaterial();
    m_manualObject = createManualObject();

    Game::sceneManager()->getRootSceneNode()->attachObject(m_manualObject);
}

debug::ColliderDrawer::~ColliderDrawer() {
    Game::sceneManager()->destroyManualObject(m_manualObject);
}

void debug::ColliderDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
    m_lines.emplace_back(Ogre::Vector3(from.x(), from.y(), from.z()));
    m_lines.emplace_back(Ogre::Vector3(to.x(), to.y(), to.z()));
}

void debug::ColliderDrawer::render() {
    if (m_lines.empty()) return;

    m_manualObject->clear();
    m_manualObject->begin(m_material, Ogre::RenderOperation::OT_LINE_LIST);

    for (size_t i = 0; i < m_lines.size(); i++) {
        m_manualObject->position(m_lines[i]);
        m_manualObject->colour(0.0, 1.0, 0.0);
    }

    m_manualObject->end();
    m_lines.clear();
}

Ogre::MaterialPtr debug::ColliderDrawer::createMaterial() {
    const std::string materialName = "CollidersWireframe";

    auto material = Game::materialManager()->getByName(materialName);

    if(material.get() != nullptr)
        return material;

    material = Game::materialManager()->create(materialName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    material->setReceiveShadows(false);

    auto* pass = material->getTechnique(0)->getPass(0);

    pass->setDepthCheckEnabled(true);
    pass->setDepthFunction(Ogre::CMPF_LESS_EQUAL);
    pass->setDepthWriteEnabled(false);
    pass->setDepthBias(1.0, 1.0);
    pass->setCullingMode(Ogre::CULL_NONE);
    pass->setLightingEnabled(false);
    pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    pass->setPolygonMode(Ogre::PM_WIREFRAME);
    pass->setDiffuse(1.0, 1.0, 1.0, 1.0);
    pass->setVertexColourTracking(Ogre::TVC_DIFFUSE);

    return material;
}

Ogre::ManualObject* debug::ColliderDrawer::createManualObject() {
    const auto manualObject = Game::sceneManager()->createManualObject("PhysicsDebugDrawer");

    manualObject->setDynamic(true);
    manualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_MAIN + 1); // Render colliders after scene

    return manualObject;
}

} // end namespace core