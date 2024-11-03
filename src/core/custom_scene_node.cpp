#include "custom_scene_node.hpp"

#include "objects/transform.hpp"

using namespace Ogre;

namespace core {

CustomSceneNode::CustomSceneNode(SceneManager* creator, const std::string& name)
    : SceneNode(creator, name)
{
    m_transform = static_cast<Transform*>(mCreator->createMovableObject("Transform"));
    this->SceneNode::attachObject(m_transform);
}

CustomSceneNode* CustomSceneNode::createChildSceneNode(const Vector3& translate, const Quaternion& rotate) {
    auto* node = SceneNode::createChildSceneNode(translate, rotate);

    // We assume that current scene manager is @CustomSceneManager, which creates CustomSceneNode
    return static_cast<CustomSceneNode*>(node);
}

CustomSceneNode* CustomSceneNode::createChildSceneNode(const std::string& name, const Vector3& translate, const Quaternion& rotate) {
    auto* node = SceneNode::createChildSceneNode(name, translate, rotate);

    // We assume that current scene manager is @CustomSceneManager, which creates CustomSceneNode
    return static_cast<CustomSceneNode*>(node);
}

std::shared_ptr<TransformState> CustomSceneNode::transformState() const {
    return m_transform->transformState();
}

} // end namespace core
