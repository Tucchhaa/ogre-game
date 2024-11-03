#pragma once

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

#include "objects/transform.hpp"

namespace core {

class Transform;
class TransformState;

class CustomSceneNode : public Ogre::SceneNode {
public:
    explicit CustomSceneNode(Ogre::SceneManager* creator)
        : CustomSceneNode(creator, Ogre::BLANKSTRING) { }

    CustomSceneNode(Ogre::SceneManager* creator, const std::string& name);

    Transform* transform() const { return m_transform; }
    std::shared_ptr<TransformState> transformState() const;

    CustomSceneNode* createChildSceneNode(
        const Ogre::Vector3& translate = Ogre::Vector3::ZERO,
        const Ogre::Quaternion& rotate = Ogre::Quaternion::IDENTITY
    ) override;

    CustomSceneNode* createChildSceneNode(
        const std::string& name,
        const Ogre::Vector3& translate = Ogre::Vector3::ZERO,
        const Ogre::Quaternion& rotate = Ogre::Quaternion::IDENTITY
    ) override;

private:
    Transform* m_transform;
};

} // end namespace core
