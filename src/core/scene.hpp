#pragma once

#include <OGRE/Ogre.h>

namespace core {

class Scene : public Ogre::FrameListener {
public:
    ~Scene() override = default;

    virtual void init();

    Ogre::Camera* mainCamera = nullptr;

    bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;

protected:
    Ogre::SceneNode* m_rootNode = nullptr;
    Ogre::SceneManager* m_sceneManager = nullptr;
};

} // end namespace core