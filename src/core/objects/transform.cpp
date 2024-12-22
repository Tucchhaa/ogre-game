#include "transform.hpp"

#include "../scene/custom_scene_node.hpp"

using namespace Ogre;

namespace core {

void Transform::sceneInited() {
    resetState();
}

void Transform::resetState() const {
    const auto* node = getParentNode();

    m_state->resetValues(
        node->getPosition(),
        node->getOrientation()
    );
}

void Transform::updateNodeTransform() const {
    Vector3 position;
    Quaternion rotation;
    auto* node = getParentNode();

    m_state->getValues(position, rotation);

    node->setPosition(position);
    node->setOrientation(rotation);

    node->_update(true, true);
}

} // end namespace core