#include "input.hpp"

void BaseInput::frameRendered(const Ogre::FrameEvent& evt) {
    for(auto& it: m_keyState) {
        if(it.second == KeyState::Down) {
            it.second = KeyState::Pressed;
        }
    }
}

void Input::frameRendered(const Ogre::FrameEvent& evt) {
    BaseInput::frameRendered(evt);

    readInput();
}

bool Input::isKeyUp(const Key keycode) {
    return m_keyState[static_cast<int>(keycode)] == KeyState::Up;
}

bool Input::isKeyDown(const Key keycode) {
    return m_keyState[static_cast<int>(keycode)] == KeyState::Down;
}

bool Input::isKeyPressed(const Key keycode) {
    const auto value = m_keyState[static_cast<int>(keycode)];

    return value == KeyState::Down || value == KeyState::Pressed;
}

void Input::readInput() {
    const float posX = isKeyPressed(Key::D) ? 1.0 : 0.0;
    const float negX = isKeyPressed(Key::A) ? 1.0 : 0.0;
    const float posY = isKeyPressed(Key::W) ? 1.0 : 0.0;
    const float negY = isKeyPressed(Key::A) ? 1.0 : 0.0;

    m_deltaX = posX - negX;
    m_deltaY = posY - negY;

    m_shift = isKeyPressed(Key::SHIFT);
    m_escape = isKeyPressed(Key::ESCAPE);
}
