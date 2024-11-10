#include "lan_menu.hpp"

#include <iostream>

#include "ui_manager.hpp"

namespace game {

LANMenu::LANMenu(OgreBites::TrayManager* trayManager, UIManager* uiManager)
{
    m_trayManager = trayManager;
    m_uiManager = uiManager;
}

void LANMenu::initOverlay()
{
    // Enable cursor
    m_trayManager->showCursor();
    // Add Mission menu button
    lanMenuWidgets.push_back(m_trayManager->createButton(OgreBites::TL_CENTER,"ClientButton","Client"));
    // Add LAN menu button
    lanMenuWidgets.push_back(m_trayManager->createButton(OgreBites::TL_CENTER,"HostButton","Host"));
    // Add Return button
    lanMenuWidgets.push_back(m_trayManager->createButton(OgreBites::TL_BOTTOMLEFT,"ReturnButton","Return"));

}

void LANMenu::buttonHit(OgreBites::Button* button)
{
    if (button == nullptr) {
        std::cerr << "Error: button is null in buttonHit." << std::endl;
        return;
    }
    if (button->getName() == "ClientButton")
    {
        m_trayManager->destroyAllWidgetsInTray(OgreBites::TL_CENTER);
        printf("Client button pressed\n");
        // ===================================
        // Here Launch the search for hosts
        // then regroup all hosts in a string vector
        // finally create custom widget
        // ===================================
        std::vector<std::string> host_list = {
            "192.168.0.1",
            "192.168.1.1",
            "10.0.0.1",
            "10.0.1.1",
            "172.16.0.1",
            "172.16.1.1",
            "8.8.8.8",
            "8.8.4.4",
            "1.1.1.1",
            "1.0.0.1"
        }; // Change this to whatever string you actually want !
        createWidget(host_list);
    }
    else if (button->getName() == "HostButton")
    {

    }
    else if (button->getName() == "ReturnButton")
    {
        m_uiManager->show_MainMenu();
    }
}

void LANMenu::createWidget(const std::vector<std::string>& lines)
{
    for (size_t i = 0; i < lines.size(); ++i) {
        std::string line = lines[i];
        std::string labelName = "LineLabel" + std::to_string(i);
        std::string buttonName = "LineButton" + std::to_string(i);

        // Créer un conteneur horizontal pour aligner le texte et le bouton
        OgreBites::TrayLocation rowLocation = static_cast<OgreBites::TrayLocation>(OgreBites::TL_CENTER);

        // Créer le label pour la ligne de texte
        m_trayManager->createLabel(rowLocation, labelName, line, 300); // Largeur pour aligner les textes

        // Créer le bouton pour cette ligne
        OgreBites::Button* button = m_trayManager->createButton(rowLocation, buttonName, "Action " + std::to_string(i + 1), 100); // Largeur bouton
        buttonLines[button] = line;  // Associer le bouton à la ligne de texte
    }
}

} // end namespace game