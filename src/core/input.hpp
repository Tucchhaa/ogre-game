#pragma once

#include <map>

#include "OgreApplicationContext.h"
#include "SDL2/SDL_keycode.h"

enum class Key {
    W = SDLK_w,
    A = SDLK_a,
    S = SDLK_s,
    D = SDLK_d,
    SHIFT = SDLK_LSHIFT,
    ESCAPE = SDLK_ESCAPE
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

    std::map<SDL_Keycode, KeyState> m_keyState;

    void frameRendered(const Ogre::FrameEvent& evt) override;

    bool keyPressed(const OgreBites::KeyboardEvent& evt) override {
        m_keyState[evt.keysym.sym] = KeyState::Down;
        return false;
    }

    bool keyReleased(const OgreBites::KeyboardEvent& evt) override {
        m_keyState[evt.keysym.sym] = KeyState::Up;
        return false;
    }
};

class Input : public BaseInput {
public:

    void frameRendered(const Ogre::FrameEvent& evt) override;

    float deltaX() const { return m_deltaX; }
    float deltaY() const { return m_deltaY; }
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
