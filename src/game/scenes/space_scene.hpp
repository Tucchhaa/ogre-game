#pragma once

#include "core/scene/scene.hpp"

namespace game {

class Fighter;

class SpaceScene : public core::Scene {
    void init() override;

    void createCamera();

    void createLight() const;

    void createDummy() const;

    void createStarFighter();

    void createStarship5() const;

    void createAsteroids() const;

    void createEarth() const;

private:
    std::shared_ptr<Fighter> m_playerFighter;
};

} // end namespace game
