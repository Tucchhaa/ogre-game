#include "free_character_controller.hpp"

#include "../input.hpp"
#include "../window_manager.hpp"

namespace core {

FreeCameraController::FreeCameraController(const Ogre::String& name): BaseMovableObject(name) {}

void FreeCameraController::update(float dt) {
    // rotation
    if(Game::windowManager()->relativeMouseEnabled()) {
        // Don't multiply by timeSinceLastFrame because mouseDeltaX/Y are already frame-rate independent
        const float rx = -Game::input()->mouseDeltaX() * angularSpeed;
        const float ry = -Game::input()->mouseDeltaY() * angularSpeed;

        getParentNode()->yaw(Ogre::Radian(rx), Ogre::Node::TS_WORLD);
        getParentNode()->pitch(Ogre::Radian(ry));
    }

    // translation
    const float x = Game::input()->deltaX() * dt * linearSpeed;
    const float z = Game::input()->deltaY() * dt * linearSpeed;

    getParentNode()->translate(x, 0, -z, Ogre::Node::TS_LOCAL);
}

} // end namespace core