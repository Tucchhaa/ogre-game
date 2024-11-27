#pragma once

#include <OgreSceneManager.h>

#include "custom_scene_node.hpp"

namespace core {

class Collider;

const Ogre::String CUSTOM_SCENE_MANAGER_TYPE = "CustomSceneManager";

class CustomSceneManager : public Ogre::SceneManager {
public:
    explicit CustomSceneManager(const std::string& instanceName)
        : SceneManager(instanceName) { }

    const std::string& getTypeName() const override { return CUSTOM_SCENE_MANAGER_TYPE; }

    Transform* createTransform();
    Transform* createTransform(const std::string& name);

    Collider* createCollider();
    Collider* createCollider(const std::string& name);

private:
    Ogre::SceneNode* createSceneNodeImpl() override;

    Ogre::SceneNode* createSceneNodeImpl(const std::string& name) override;
};

class CustomSceneManagerFactory : public Ogre::SceneManagerFactory {
public:
    Ogre::SceneManager* createInstance(const std::string& instanceName) override {
        return new CustomSceneManager(instanceName);
    }

    const std::string& getTypeName() const override {
        return CUSTOM_SCENE_MANAGER_TYPE;
    }
};

} // end namespace core