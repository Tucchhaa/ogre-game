#pragma once
#include <memory>

#include "core/scene/scene.hpp"

namespace game {
class Environment;
class Fighter;

class SpaceScene : public core::Scene {
public:
    SpaceScene();

    void init() override;

    void start() override;

    void update(float dt);

private:
    std::shared_ptr<Environment> m_environment;

    std::shared_ptr<Fighter> m_fighter;
};

} // end namespace game
