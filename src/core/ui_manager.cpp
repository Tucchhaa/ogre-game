#include "ui_manager.hpp"

#include "game.hpp"

void core::UIListener::hide() {
    Game::trayManager()->destroyAllWidgets();
}

void core::UIManager::addListener(const std::shared_ptr<UIListener>& listener) {
    const std::string name = listener->getName();

    if(m_listeners.find(name) != m_listeners.end()) {
        throw std::runtime_error("UI listener with the specified name already exists");
    }

    m_listeners[name] = listener;
}

void core::UIManager::showOnly(const std::string& name) {
    for(auto& it : m_listeners) {
        if(it.first != name) {
            it.second->hide();
        }
    }

    const auto listener = m_listeners[name];

    // created widgets will notify current listener on events.
    // So set listener before creating any widgets
    Game::trayManager()->setListener(listener.get());
    listener->show();
}
