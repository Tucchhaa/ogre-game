#include "base_movable_object.hpp"

#include "../scene/custom_scene_node.hpp"

namespace core {

std::map<int, BaseMovableObject*> BaseMovableObject::m_instances;

std::shared_ptr<TransformState> BaseMovableObject::transformState() const {
    return getCustomNode()->transformState();
}

CustomSceneNode* BaseMovableObject::getCustomNode() const {
    return static_cast<CustomSceneNode*>(getParentSceneNode());
}

} // end namespace core