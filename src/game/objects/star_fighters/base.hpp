#pragma once
#include <string>

#include "core/game_event_listener.hpp"

namespace core {
class Collider;
class CustomSceneNode;
}

namespace game {

class FighterIndicators;
class StarFighterController;

class BaseStarFighter : core::GameEventListener {
public:
    virtual ~BaseStarFighter() = default;

    explicit BaseStarFighter(const std::string &model);

    std::shared_ptr<FighterIndicators> indicators() const { return m_indicators; }

    core::CustomSceneNode* node() const { return m_node; }

protected:
    const int ID;
    core::CustomSceneNode* m_wrapperNode;
    core::CustomSceneNode* m_node;

    StarFighterController* m_controller;
    std::shared_ptr<FighterIndicators> m_indicators;

    virtual void primaryAttack(float dt) = 0;

    virtual void secondaryAttack(float dt) = 0;

    void fixedUpdate(float dt) override;

private:
    static int generateID() {
        static int cnt = 0;
        return ++cnt;
    }

    static core::Collider* createCollider(const std::string& convexHullFile);
};

} // end namespace game