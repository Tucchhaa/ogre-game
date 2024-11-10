#include "lan_menu.hpp"

#include "../../core/game.hpp"

namespace game {

void LANMenu::show() {
    const auto tray = core::Game::trayManager();
    tray->showCursor();

    widgets.insert(widgets.end(), {
        tray->createButton(OgreBites::TL_CENTER,"ClientButton","Client"),
        tray->createButton(OgreBites::TL_CENTER,"HostButton","Host"),
        tray->createButton(OgreBites::TL_BOTTOMLEFT,"ReturnButton","Return")
    });
}

void LANMenu::hide() {
    for(auto& widget: widgets) {
        core::Game::trayManager()->destroyWidget(widget);
    }

    widgets.clear();
}

void LANMenu::buttonHit(OgreBites::Button* button)
{
    if (button == nullptr) {
        return;
    }

    if (button->getName() == "ClientButton") {
        core::Game::trayManager()->destroyAllWidgetsInTray(OgreBites::TL_CENTER);

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
        };
        createWidget(host_list);
    }
    else if (button->getName() == "HostButton") {

    }
    else if (button->getName() == "ReturnButton") {
        core::Game::UIManager()->showOnly("MAIN_MENU");
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
        core::Game::trayManager()->createLabel(rowLocation, labelName, line, 300); // Largeur pour aligner les textes

        // Créer le bouton pour cette ligne
        OgreBites::Button* button = core::Game::trayManager()->createButton(rowLocation, buttonName, "Action " + std::to_string(i + 1), 100); // Largeur bouton
        buttonLines[button] = line;  // Associer le bouton à la ligne de texte
    }
}

} // end namespace game