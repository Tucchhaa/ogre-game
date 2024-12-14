#include "fighter_indicators.hpp"

#include <OgreTrays.h>

game::FighterIndicators::FighterIndicators() {
    m_manager = core::Game::overlayManager();

    m_overlay = m_manager->getByName("FighterIndicators");
}

void game::FighterIndicators::show() {
    core::Game::trayManager()->hideCursor();
    resize();
    m_overlay->show();
}

void game::FighterIndicators::resize() const {
    auto aim = m_manager->getOverlayElement("Aim");
    auto posX = (core::Game::windowWidth() - aim->getWidth())/2;
    auto posY = (core::Game::windowHeight() - aim->getHeight())/2;

    aim->setMetricsMode(Ogre::GMM_PIXELS);
    aim->setPosition(posX, posY);
}

Ogre::OverlayContainer* game::FighterIndicators::createContainer(const std::string& name) const {
    auto* element = m_manager->createOverlayElement("Panel", name);
    auto* container = static_cast<Ogre::OverlayContainer*>(element);

    return container;
}

void game::FighterIndicators::updateBottomLeftIndicators() const {

}

void game::FighterIndicators::updateAmmoIndicators(int currentAmmo, int maxAmmo) const {
    const auto primaryAmmoText = m_manager->getOverlayElement("PrimaryAmmo_Text");
    const auto maxPrimaryAmmoText = m_manager->getOverlayElement("MaxPrimaryAmmo_Text");

    primaryAmmoText->setCaption(std::to_string(currentAmmo));
    maxPrimaryAmmoText->setCaption(" / " + std::to_string(maxAmmo));
}
