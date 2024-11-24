#pragma once

#include "core/scene/scene.hpp"

namespace game {

class SpaceScene : public core::Scene {
    void init() override;

    void createCamera();

    void createLight() const;

    void createDummy() const;

    void createStarFighter() const;

    void createAsteroids() const;

    void createEarth() const;

    void start() override {

    }
};

} // end namespace game
