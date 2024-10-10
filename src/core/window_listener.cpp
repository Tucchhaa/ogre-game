#include "window_listener.hpp"

#include <SDL2/SDL.h>

#include "game.hpp"

namespace core {

WindowManager::WindowManager() {
    OgreBites::WindowEventUtilities::addWindowEventListener(
        Game::renderWindow(), new Listener(this)
    );
}

void WindowManager::updateRelativeMouseMode() const {
    bool enabled = Game::renderWindow()->isActive() && m_relativeMouseEnabled;
    SDL_SetRelativeMouseMode(enabled ? SDL_TRUE : SDL_FALSE);
}

} // end namespace core