#pragma once

#include <Bites/OgreWindowEventUtilities.h>

namespace core {

/**
 * Manages window events and mouse input modes.
 */
class WindowManager {
public:
    WindowManager();

    /**
     * If relative mouse is enabled, the mouse cursor will be hidden and the
     * mouse will be locked in the center of the screen
     */
    void relativeMouseEnabled(bool value) {
        m_relativeMouseEnabled = value;
        updateRelativeMouseMode();
    }
    bool relativeMouseEnabled() const {
        return m_relativeMouseEnabled;
    }

    void windowFocusChange() const {
        updateRelativeMouseMode();
    }

private:
    bool m_relativeMouseEnabled = false;

    void updateRelativeMouseMode() const;

    class Listener : public OgreBites::WindowEventListener {
    public:
        explicit Listener(WindowManager* manager): m_manager(manager) {}

        void windowFocusChange(Ogre::RenderWindow*) override { m_manager->windowFocusChange(); }

    private:
        WindowManager* m_manager;
    };
};

} // end namespace core
