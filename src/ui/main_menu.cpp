//
// Created by vince on 01/11/2024.
//


#include "main_menu.h"

#include <iostream>

#include <SDL_main.h>

// #include "lan_menu.h"
#include "UI_Manager.h"

MainMenu::MainMenu(Ogre::Root* root, OgreBites::TrayManager* trayManager, UI_Manager* uiManager)
{
    m_root = root;
    m_uiManager = uiManager;
    m_trayManager = trayManager;

}


void MainMenu::initOverlay()
{
    // Enable cursor
    m_trayManager->showCursor();
    // Add Mission menu button
    mainMenuWidgets.push_back(m_trayManager->createButton(OgreBites::TL_CENTER,"MissionButton","Missions"));
    // Add LAN menu button
    mainMenuWidgets.push_back(m_trayManager->createButton(OgreBites::TL_CENTER,"LanButton","LAN"));
    // Add Settings menu button
    mainMenuWidgets.push_back(m_trayManager->createButton(OgreBites::TL_CENTER,"SettingsButton","Settings"));
    // Add Exit menu button
    mainMenuWidgets.push_back(m_trayManager->createButton(OgreBites::TL_CENTER,"ExitButton","Exit"));
}

void MainMenu::buttonHit(OgreBites::Button* button)
{
    if (button->getName() == "MissionButton")
    {

    }
    else if (button->getName() == "LanButton")
    {
        std::cout << "Address of trayManager: " << m_trayManager << std::endl;
        m_uiManager->show_LanMenu();
    }
    else if (button->getName() == "SettingsButton")
    {

    }
    else if (button->getName() == "ExitButton")
    {
        m_root->queueEndRendering();
    }
}

