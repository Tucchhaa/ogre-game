#pragma once

#include "../game.hpp"
#include "OgreMovableObject.h"

namespace core {

/**
 * Do not use this class directly. Instead, extend it for your custom objects.
 *
 * This class provides default implementations for abstract functions from @link Ogre::MovableObject
 * and integrates @link Ogre::FrameListener for frame callbacks in derived classes
 *
 * You must implement @link Ogre::MovableObject::getMovableType() in your derived class.
 */
class BaseMovableObject : public Ogre::MovableObject, public Ogre::FrameListener {
public:
    BaseMovableObject() {
        Game::root()->addFrameListener(this);
    };
    explicit BaseMovableObject(const Ogre::String& name): MovableObject(name) {
        Game::root()->addFrameListener(this);
    }

    const Ogre::AxisAlignedBox& getBoundingBox() const override {
        static Ogre::AxisAlignedBox box;
        return box;
    }

    Ogre::Real getBoundingRadius() const override {
        return 10.0f;
    };

    void _updateRenderQueue(Ogre::RenderQueue* queue) override {}

    void visitRenderables(Ogre::Renderable::Visitor* visitor, bool debugRenderables) override {}
};

} // end namespace core
