#pragma once

#include <map>

#include <OgreApplicationContext.h>
#include <SDL2/SDL_keycode.h>

namespace core {

enum class Key {
    W = SDLK_w,
    A = SDLK_a,
    S = SDLK_s,
    D = SDLK_d,
    SHIFT = SDLK_LSHIFT,
    ESCAPE = SDLK_ESCAPE,
    SPACE = SDLK_SPACE
};

/**
 * Don't use it directly. Use @link Input class instead
 */
class BaseInput : public OgreBites::InputListener {
protected:
    enum class KeyState {
        None,
        Up,
        Down,
        Pressed
    };

    struct MouseState {
        int posX = 0;
        int posY = 0;
        int deltaX = 0;
        int deltaY = 0;
        bool leftButtonClicked = false;
    };

    std::map<SDL_Keycode, KeyState> m_keyState;
    MouseState m_mouseState;

    void frameRendered(const Ogre::FrameEvent& evt) override;

    bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

    bool keyReleased(const OgreBites::KeyboardEvent& evt) override;

    bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override;

    bool mousePressed(const OgreBites::MouseButtonEvent& evt) override;

    bool mouseReleased(const OgreBites::MouseButtonEvent& evt) override;
};

class Input : public BaseInput {
public:

    void frameRendered(const Ogre::FrameEvent& evt) override;

    float deltaX() const { return m_deltaX; }
    float deltaY() const { return m_deltaY; }
    float mouseDeltaX() const;
    float mouseDeltaY() const;
    bool shift() const { return m_shift; }
    bool escape() const { return m_escape; }

    /**
     * @return true, if key was released this frame
     */
    bool isKeyUp(Key keycode);

    /**
     * @return true, if key was just pressed this frame
     */
    bool isKeyDown(Key keycode);

    /**
     * @return true, if key was still pressed this frame
     */
    bool isKeyPressed(Key keycode);

private:
    void readInput();

    float m_deltaX = 0;
    float m_deltaY = 0;
    bool m_shift = false;
    bool m_escape = false;
};

} // end namespace core