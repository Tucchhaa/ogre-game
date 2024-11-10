#pragma once

#include <OgreTrays.h>

namespace game {

class UIListener
{
public:
    virtual ~UIListener() = default;
    UIListener(){};

    virtual void initOverlay(){};

    virtual void buttonHit(OgreBites::Button* button){}
    virtual void itemSelected(OgreBites::SelectMenu* menu) {}
    virtual void labelHit(OgreBites::Label* label) {}
    virtual void sliderMoved(OgreBites::Slider* slider) {}
    virtual void checkBoxToggled(OgreBites::CheckBox* box) {}
    virtual void okDialogClosed(const Ogre::DisplayString& message) {}
    virtual void yesNoDialogClosed(const Ogre::DisplayString& question, bool yesHit) {}
};

} // end namespace game