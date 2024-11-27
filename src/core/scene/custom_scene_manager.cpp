#include "custom_scene_manager.hpp"

#include "core/objects/collider.hpp"
#include "core/objects/transform.hpp"

namespace core {

Transform* CustomSceneManager::createTransform() {
    auto* object = createMovableObject("Transform");
    return static_cast<Transform*>(object);
}

Transform* CustomSceneManager::createTransform(const std::string& name) {
    auto* object = createMovableObject("Transform");
    return static_cast<Transform*>(object);
}

Collider* CustomSceneManager::createCollider() {
    auto* object = createMovableObject("Collider");
    return static_cast<Collider*>(object);
}

Collider* CustomSceneManager::createCollider(const std::string& name) {
    auto* object = createMovableObject(name, "Collider");
    return static_cast<Collider*>(object);
}

Ogre::SceneNode* CustomSceneManager::createSceneNodeImpl() {
    return new CustomSceneNode(this);
}

Ogre::SceneNode* CustomSceneManager::createSceneNodeImpl(const std::string& name) {
    return new CustomSceneNode(this, name);
}


} // end namespace core