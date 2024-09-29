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
    BaseMovableObject() { init(); }
    explicit BaseMovableObject(const Ogre::String& name): MovableObject(name) { init(); }

    // ===
    // MovableObject overrides
    // ===
    const Ogre::AxisAlignedBox& getBoundingBox() const override {
        static Ogre::AxisAlignedBox box;
        return box;
    }

    Ogre::Real getBoundingRadius() const override {
        return 10.0f;
    };

    void _updateRenderQueue(Ogre::RenderQueue* queue) override {}

    void visitRenderables(Ogre::Renderable::Visitor* visitor, bool debugRenderables) override {}

protected:
    void init() {
        Game::root()->addFrameListener(this);
        setListener(new Listener());
    }

    // ===
    // MovableObject lifecycle events
    // ===
    virtual void objectDestroyed() {}

    virtual void objectAttached() {}

    virtual void objectDetached() {}

    virtual void objectMoved() {}

private:
    class Listener final : public MovableObject::Listener {
        void objectDestroyed(MovableObject* object) override
            { dynamic_cast<BaseMovableObject*>(object)->objectDestroyed(); }

        void objectAttached(MovableObject* object) override
            { dynamic_cast<BaseMovableObject*>(object)->objectAttached(); }

        void objectDetached(MovableObject* object) override
            { dynamic_cast<BaseMovableObject*>(object)->objectDetached(); }

        void objectMoved(MovableObject* object) override
            { dynamic_cast<BaseMovableObject*>(object)->objectMoved(); }
    };
};

} // end namespace core
