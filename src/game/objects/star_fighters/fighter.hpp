#pragma once

#include "base.hpp"

namespace game {

class Fighter : public BaseStarFighter {
public:
    Fighter() : BaseStarFighter("StarFighter01.fbx") {}
};

} // end namespace game