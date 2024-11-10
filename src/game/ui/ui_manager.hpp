#pragma once

#include <OgreTrays.h>

#include "ui_listener.hpp"

namespace game {

class UIManager: public OgreBites::TrayListener
{
public:
    UIManager(Ogre::Root*, Ogre::SceneManager*, OgreBites::TrayManager* );
    void createMenuScene();

    void init_MainMenu();
    void init_LanMenu();

    void show_LanMenu();
    void show_MainMenu();

    Ogre::Camera* getCamera();

    void buttonHit(OgreBites::Button* button) override;
    // void itemSelected(OgreBites::SelectMenu* menu) {}
    // void labelHit(OgreBites::Label* label) {}
    // void sliderMoved(OgreBites::Slider* slider) {}
    // void checkBoxToggled(OgreBites::CheckBox* box) {}
    // void okDialogClosed(const Ogre::DisplayString& message) {}
    // void yesNoDialogClosed(const Ogre::DisplayString& question, bool yesHit) {}

private:
    Ogre::Root* m_root;
    Ogre::SceneManager* m_scene_manager;
    OgreBites::TrayManager* m_tray_manager;
    Ogre::Camera* m_camera{};
    UIListener* current_tray_listener;

    //Custom TrayListeners for each menu page
    UIListener* lan_tray_listener;
    UIListener* main_menu_tray_listener;
};

} // end namespace game