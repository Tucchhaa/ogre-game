#pragma once
#include <string>

namespace game {
class StarFighterController;
}

namespace core {
class CustomSceneNode;
}

namespace game {

class BaseStarFighter {
public:
    BaseStarFighter(const std::string &model);

private:
    const int ID;

    core::CustomSceneNode* m_node;
    StarFighterController* m_controller;

    static int generateID() {
        static int cnt = 0;
        return ++cnt;
    }
};

} // end namespace game