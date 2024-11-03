//
// Created by vince on 02/11/2024.
//

#ifndef LAN_MENU_H
#define LAN_MENU_H
#include <OgreTrays.h>

#include "Tray_Listener.h"

#endif //LAN_MENU_H

class UI_Manager;

class LAN_Menu : public Tray_Listener
{
public:
    LAN_Menu(OgreBites::TrayManager* , UI_Manager*);

    void initOverlay() override;
    void createWidget(const std::vector<std::string>&);

    void buttonHit(OgreBites::Button* button) override;
    void itemSelected(OgreBites::SelectMenu* menu) override {}
    void labelHit(OgreBites::Label* label) override {}
    void sliderMoved(OgreBites::Slider* slider) override {}
    void checkBoxToggled(OgreBites::CheckBox* box) override {}
    void okDialogClosed(const Ogre::DisplayString& message) override {}
    void yesNoDialogClosed(const Ogre::DisplayString& question, bool yesHit) override {}
protected:
    std::vector<OgreBites::Widget*> lanMenuWidgets;
    OgreBites::TrayManager* m_trayManager;
    std::map<OgreBites::Button*, std::string> buttonLines;
    UI_Manager* m_uiManager;
};
