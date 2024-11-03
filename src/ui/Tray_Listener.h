//
// Created by vince on 01/11/2024.
//
#pragma once

#ifndef TRAY_LISTENER_H
#define TRAY_LISTENER_H
#include <OgreTrays.h>

#endif //TRAY_LISTENER_H

class Tray_Listener
{
public:
    virtual ~Tray_Listener() = default;
    Tray_Listener(){};

    virtual void initOverlay(){};

    virtual void buttonHit(OgreBites::Button* button){}
    virtual void itemSelected(OgreBites::SelectMenu* menu) {}
    virtual void labelHit(OgreBites::Label* label) {}
    virtual void sliderMoved(OgreBites::Slider* slider) {}
    virtual void checkBoxToggled(OgreBites::CheckBox* box) {}
    virtual void okDialogClosed(const Ogre::DisplayString& message) {}
    virtual void yesNoDialogClosed(const Ogre::DisplayString& question, bool yesHit) {}
};
