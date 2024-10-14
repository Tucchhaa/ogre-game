#pragma once

#include <OgreMovableObject.h>

#include "../game_event_listener.hpp"
#include "../objects/state.hpp"

class State;

namespace core {

/** *
 * This class provides default implementations for abstract functions from @link Ogre::MovableObject
 * and integrates @link Ogre::FrameListener for frame callbacks in derived classes
 *
 * You must implement @link Ogre::MovableObject::getMovableType() in your derived class.
 */
class BaseMovableObject : public Ogre::MovableObject, GameEventListener {
public:
    const int ID;

    BaseMovableObject(): ID(generateID())
        { init(); }
    explicit BaseMovableObject(const Ogre::String& name): MovableObject(name), ID(generateID())
        { init(); }

    ~BaseMovableObject() {
        m_instances.erase(m_instances.find(ID));
    }

    virtual shared_ptr<State> state() { return nullptr; }

    static map<int, BaseMovableObject*> instances() { return m_instances; }

    // ===
    // MovableObject overrides
    // ===

    const Ogre::AxisAlignedBox& getBoundingBox() const override {
        static Ogre::AxisAlignedBox box;
        return box;
    }

    Ogre::Real getBoundingRadius() const override { return 10.0f; }

    void _updateRenderQueue(Ogre::RenderQueue*) override {}

    void visitRenderables(Ogre::Renderable::Visitor*, bool) override {}

protected:

    // ===
    // MovableObject lifecycle events
    // ===

    virtual void objectDestroyed() {}

    virtual void objectAttached() {}

    virtual void objectDetached() {}

    virtual void objectMoved() {}

private:
    static map<int, BaseMovableObject*> m_instances;

    static int generateID() {
        static int lastID = 0;
        return ++lastID;
    }

    void init() {
        setListener(new Listener(this));
        m_instances[ID] = this;
    }

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
};

} // end namespace core
