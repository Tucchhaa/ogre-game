#include "free_character_controller.hpp"

namespace core {

FreeCameraController::FreeCameraController(const Ogre::String& name): BaseMovableObject(name) {}

bool FreeCameraController::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    bool isRotation = Game::input()->shift();
    float x = Game::input()->deltaX() * evt.timeSinceLastFrame;
    float z = Game::input()->deltaY() * evt.timeSinceLastFrame;

    if(isRotation) {
        getParentNode()->yaw(Ogre::Radian(-x * angluarSpeed), Ogre::Node::TS_WORLD);
        getParentNode()->pitch(Ogre::Radian(-z * angluarSpeed));
    }
    else { // translation
        getParentNode()->translate(x * linearSpeed, 0, -z * linearSpeed, Ogre::Node::TS_LOCAL);
    }

    return true;
}

} // end namespace core