#pragma once

#include "base_movable_object.hpp"
#include "../game.hpp"

namespace core {

const Ogre::String FREE_CAMERA_CONTROLLER_TYPE = "FreeCameraController";

/**
 * Attach this object to a node with a @link Ogre::Camera to enable free movement in space
 */
class FreeCameraController : public BaseMovableObject {
public:
    float linearSpeed = 20.0f;
    float angluarSpeed = 2.0f;

    FreeCameraController() = default;
    explicit FreeCameraController(const Ogre::String& name);

    const Ogre::String& getMovableType() const override { return FREE_CAMERA_CONTROLLER_TYPE; }

    bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;
};

class FreeCameraControllerFactory : public Ogre::MovableObjectFactory {
    Ogre::MovableObject* createInstanceImpl(const Ogre::String& name, const Ogre::NameValuePairList* params) override {
        return new FreeCameraController(name);
    }

public:
    const Ogre::String& getType() const override { return FREE_CAMERA_CONTROLLER_TYPE; };
};

} // end namespace core