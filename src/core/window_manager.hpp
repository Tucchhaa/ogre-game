#pragma once

namespace core {

/**
 * Manages window events and mouse input modes.
 */
class WindowManager {
public:
    WindowManager() = default;

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

    /**
     * Need to implement Windows Event Listener, which will listen
     * to window focus change and invoke this function
     */
    void windowFocusChange() const {
        updateRelativeMouseMode();
    }

private:
    bool m_relativeMouseEnabled = false;

    void updateRelativeMouseMode() const;
};

} // end namespace core
