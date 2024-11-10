//
// Created by vince on 01/11/2024.
//

#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <OgreTrays.h>
#include <vector>

#include "Tray_Listener.h"

#endif //MAIN_MENU_H

class UI_Manager;

class MainMenu: public Tray_Listener
{
public:
    MainMenu(Ogre::Root*, OgreBites::TrayManager*, UI_Manager*);


    void initOverlay() override;
    void buttonHit(OgreBites::Button* button) override;
    void itemSelected(OgreBites::SelectMenu* menu) override {}
    void labelHit(OgreBites::Label* label) override {}
    void sliderMoved(OgreBites::Slider* slider) override {}
    void checkBoxToggled(OgreBites::CheckBox* box) override {}
    void okDialogClosed(const Ogre::DisplayString& message) override {}
    void yesNoDialogClosed(const Ogre::DisplayString& question, bool yesHit) override {}

protected:
    std::vector<OgreBites::Widget*> mainMenuWidgets;
    OgreBites::TrayManager* m_trayManager;
    Ogre::Root* m_root;
    UI_Manager* m_uiManager;
};
