//
// Created by vince on 03/11/2024.
//

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <OgreTrays.h>

#include "Tray_Listener.h"


#endif //UI_MANAGER_H
class UI_Manager: public OgreBites::TrayListener
{
public:
    UI_Manager(Ogre::Root*, Ogre::SceneManager*, OgreBites::TrayManager* );
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
    Tray_Listener* current_tray_listener;

    //Custom TrayListeners for each menu page
    Tray_Listener* lan_tray_listener;
    Tray_Listener* main_menu_tray_listener;
};