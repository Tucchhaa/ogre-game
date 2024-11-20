#include "transform.hpp"

#include "../scene/custom_scene_node.hpp"

using namespace Ogre;

namespace core {

void Transform::sceneInited() {
    updateState();
}

void Transform::update(float dt) {
    const auto* node = getParentNode();

    if(node != nullptr) {
        updateSceneNodeTransform();
    }
}

void Transform::updateState() const {
    const auto* node = getParentNode();

    m_state->resetValues(
        node->_getDerivedPosition(),
        node->_getDerivedOrientation()
    );
}

void Transform::updateSceneNodeTransform() const {
    Vector3 position;
    Quaternion rotation;
    auto* node = getParentNode();

    m_state->getValues(position, rotation);

    if(position != node->_getDerivedPosition()) {
        node->_setDerivedPosition(position);
    }

    if(rotation != node->_getDerivedOrientation()) {
        node->_setDerivedOrientation(rotation);
    }
}

} // end namespace core