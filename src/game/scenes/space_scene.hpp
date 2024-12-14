#pragma once

#include "core/scene/scene.hpp"

namespace game {

class FighterIndicators;
class Fighter;

class SpaceScene : public core::Scene {
public:
    std::shared_ptr<FighterIndicators> fighterIndicators() { return m_fighterIndicators; }

private:
    std::shared_ptr<Fighter> m_playerFighter;
    std::shared_ptr<FighterIndicators> m_fighterIndicators;

    void init() override;

    void start() override;

    void createCamera();

    void createLight() const;

    void createDummy() const;

    void createStarFighter();

    void createStarship5() const;

    void createAsteroids() const;

    void createEarth() const;

    void update(float dt);
};

} // end namespace game
