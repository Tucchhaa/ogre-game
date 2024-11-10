#include "ui_manager.hpp"

#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <SDL_main.h>

#include "lan_menu.hpp"
#include "main_menu.hpp"
#include "../galactic_wars_game.hpp"

namespace game {

UIManager::UIManager()
{
    core::Game::trayManager()->setListener(this);

    init_LanMenu();
    init_MainMenu();

    show_MainMenu();
}

void UIManager::init_MainMenu()
{
    main_menu_tray_listener = new MainMenu(core::Game::root(), core::Game::trayManager(), this);
}
void UIManager::init_LanMenu()
{
    lan_tray_listener = new LANMenu(core::Game::trayManager(), this);
}

void UIManager::buttonHit(OgreBites::Button* button)
{
    current_tray_listener->buttonHit(button);
}

void UIManager::show_LanMenu()
{
    core::Game::trayManager()->destroyAllWidgets();
    lan_tray_listener->initOverlay();
    current_tray_listener = lan_tray_listener;
}

void UIManager::show_MainMenu()
{
    core::Game::trayManager()->destroyAllWidgets();
    main_menu_tray_listener->initOverlay();
    current_tray_listener = main_menu_tray_listener;
}

Ogre::Camera* UIManager::getCamera()
{
    return m_camera;
}

} // end namespace game
