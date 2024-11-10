#pragma once

#include <OgreTrays.h>
#include <vector>

#include "ui_listener.hpp"

namespace game {

class UIManager;

class MainMenu: public UIListener
{
public:
    MainMenu(Ogre::Root*, OgreBites::TrayManager*, UIManager*);


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
    UIManager* m_uiManager;
};

} // end namespace game