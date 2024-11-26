#pragma once

#include "core/game.hpp"

#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>

namespace game {

class FighterIndicators {
public:
    FighterIndicators() {
        m_manager = core::Game::overlayManager();

        m_overlay = m_manager->getByName("FighterIndicators");
    }

    void show() {
        resize();
        m_overlay->show();
    }

    void resize() {
        auto aim = m_manager->getOverlayElement("Aim");
        auto posX = (core::Game::windowWidth() - aim->getWidth())/2;
        auto posY = (core::Game::windowHeight() - aim->getHeight())/2;

        aim->setMetricsMode(Ogre::GMM_PIXELS);
        aim->setPosition(posX, posY);
    }

private:
    Ogre::OverlayManager* m_manager;
    Ogre::Overlay* m_overlay;

    Ogre::OverlayContainer* createContainer(const std::string& name) const {
        auto* element = m_manager->createOverlayElement("Panel", name);
        auto* container = static_cast<Ogre::OverlayContainer*>(element);

        return container;
    }

    void processBottomLeftIndicators() const {

    }
};

} // end namespace game
