#include "input.hpp"

#include <SDL2/SDL.h>

#include "game.hpp"

namespace core {

void BaseInput::updateInputState() {
    for(auto& it: m_keyState) {
        if(it.second == KeyState::Down) {
            it.second = KeyState::Pressed;
        }
    }

    m_mouseState.deltaX = 0;
    m_mouseState.deltaY = 0;
}

bool BaseInput::keyPressed(const OgreBites::KeyboardEvent& evt) {
    m_keyState[evt.keysym.sym] = KeyState::Down;
    return false;
}

bool BaseInput::keyReleased(const OgreBites::KeyboardEvent& evt) {
    m_keyState[evt.keysym.sym] = KeyState::Up;
    return false;
}

bool BaseInput::mouseMoved(const OgreBites::MouseMotionEvent& evt) {
    m_mouseState.posX = evt.x;
    m_mouseState.posY = evt.y;
    m_mouseState.deltaX = evt.xrel;
    m_mouseState.deltaY = evt.yrel;
    return false;
}

bool BaseInput::mousePressed(const OgreBites::MouseButtonEvent& evt) {
    if(evt.button == SDL_BUTTON_LEFT) {
        m_mouseState.leftButtonClicked = true;
    }
    if(evt.button == SDL_BUTTON_RIGHT) {
        m_mouseState.rightButtonClicked = true;
    }

    return false;
}

bool BaseInput::mouseReleased(const OgreBites::MouseButtonEvent& evt) {
    if(evt.button == SDL_BUTTON_LEFT) {
        m_mouseState.leftButtonClicked = false;
    }
    if(evt.button == SDL_BUTTON_RIGHT) {
        m_mouseState.rightButtonClicked = false;
    }

    return false;
}

void Input::updateInputState() {
    BaseInput::updateInputState();

    const float posX = isKeyPressed(Key::D) ? 1.0 : 0.0;
    const float negX = isKeyPressed(Key::A) ? 1.0 : 0.0;
    const float posY = isKeyPressed(Key::W) ? 1.0 : 0.0;
    const float negY = isKeyPressed(Key::S) ? 1.0 : 0.0;

    m_deltaX = posX - negX;
    m_deltaY = posY - negY;
}

float Input::mouseDeltaX() const {
    const float width = static_cast<float>(Game::renderWindow()->getWidth());

    return static_cast<float>(m_mouseState.deltaX) / width;
}

float Input::mouseDeltaY() const {
    const float height = static_cast<float>(Game::renderWindow()->getHeight());

    return static_cast<float>(m_mouseState.deltaY) / height;
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

} // end namespace core