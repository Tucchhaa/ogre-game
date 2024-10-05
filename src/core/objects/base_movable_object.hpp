#pragma once

#include <OgreFrameListener.h>
#include <OgreMovableObject.h>

#include "../objects/state.hpp"

class State;

namespace core {

/** *
 * This class provides default implementations for abstract functions from @link Ogre::MovableObject
 * and integrates @link Ogre::FrameListener for frame callbacks in derived classes
 *
 * You must implement @link Ogre::MovableObject::getMovableType() in your derived class.
 */
class BaseMovableObject : public Ogre::MovableObject {
public:
    BaseMovableObject()
        { BaseMovableObject::init(); }
    explicit BaseMovableObject(const Ogre::String& name): MovableObject(name)
        { BaseMovableObject::init(); }

    /**
     * Invoked at fixed rate. All logic must be implemented here.
     * Note: This function is called in a diffrent thread (not main thread),
     * so be careful about concurrency
     */
    virtual BaseMovableObject* fixedUpdate(float dt) {
        return this;
    }

    virtual std::shared_ptr<State> state() { return nullptr; }

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

    void virtual init();

    // ===
    // MovableObject lifecycle events
    // ===

    virtual void objectDestroyed() {}

    virtual void objectAttached();

    virtual void objectDetached();

    virtual void objectMoved() {}

    // ===
    // Frame events
    // ===

    virtual void frameRenderingQueued(const Ogre::FrameEvent& evt) {}

private:
    int m_fixedUpdateCallbackId = -1;

    class Listener final : public MovableObject::Listener {
    public:
        explicit Listener(BaseMovableObject* object): m_object(object) {}

        void objectDestroyed(MovableObject*) override { m_object->objectDestroyed(); }

        void objectAttached(MovableObject*) override { m_object->objectAttached(); }

        void objectDetached(MovableObject*) override { m_object->objectDetached(); }

        void objectMoved(MovableObject*) override { m_object->objectMoved(); }

    private:
        BaseMovableObject* m_object;
    };

    class FrameListener final : public Ogre::FrameListener {
    public:
        explicit FrameListener(BaseMovableObject* object): m_object(object) {}

        bool frameRenderingQueued(const Ogre::FrameEvent& evt) override {
            m_object->frameRenderingQueued(evt);
            return true;
        }

    private:
        BaseMovableObject* m_object;
    };
};

} // end namespace core
