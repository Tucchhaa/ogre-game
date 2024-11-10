#pragma once

#include "../../core/scene.hpp"

namespace game {

class DemoScene : public core::Scene {
    void init() override;

    void createLight() const;

    void createCamera();

    void createSinbad();

    void createGround();

    void update(float dt) override;
};

} // end namespace game
