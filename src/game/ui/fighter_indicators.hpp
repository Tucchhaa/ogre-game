#pragma once

#include "core/game.hpp"

#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>

namespace game {

class FighterIndicators {
public:
    FighterIndicators();

    void show();

    void resize() const;

    void updateBottomLeftIndicators() const;

    void updateAmmoIndicators(int currentAmmo, int maxAmmo) const;

private:
    Ogre::OverlayManager* m_manager;
    Ogre::Overlay* m_overlay;

    Ogre::OverlayContainer* createContainer(const std::string& name) const;
};

} // end namespace game
