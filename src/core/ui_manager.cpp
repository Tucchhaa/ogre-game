#include "ui_manager.hpp"

#include "game.hpp"

namespace core {

UserInterface::UserInterface() {
    m_tray = Game::trayManager();
    m_ui = Game::UIManager();
    m_network = Game::networkManager();
}

void UserInterface::hide() {
    m_tray->hideCursor();
    m_tray->destroyAllWidgets();
}

void UIManager::addListener(const std::shared_ptr<UserInterface>& listener) {
    const std::string name = listener->getName();

    if(m_interfaces.find(name) != m_interfaces.end()) {
        throw std::runtime_error("UI listener with the specified name already exists");
    }

    m_interfaces[name] = listener;
}

void UIManager::showOnly(const std::string& name) {
    for(auto& it : m_interfaces) {
        if(it.first != name) {
            it.second->hide();
        }
    }

    const auto listener = m_interfaces[name];

    // created widgets will notify current listener on events.
    // So set listener before creating any widgets
    Game::trayManager()->setListener(listener.get());
    listener->show();
}

} // end namespace core
