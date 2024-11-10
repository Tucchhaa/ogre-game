#pragma once

#include <OgreTrays.h>

#include "ui_listener.hpp"

class UIManager;

class LANMenu : public UIListener
{
public:
    LANMenu(OgreBites::TrayManager* , UIManager*);

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
    UIManager* m_uiManager;
};
