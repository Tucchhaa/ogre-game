#include "state.hpp"

#include "../../game.hpp"
#include "../../utils.hpp"

using namespace std;

namespace core {

map<string, any> State::popChanges() {
    unique_lock _(m_mutex);

    map<string, any> changesCopy;
    changesCopy.swap(m_changes);

    return changesCopy;
}

Ogre::Vector3 State::interpolate(const Ogre::Vector3& a, const Ogre::Vector3& b) {
    const float f = calcInterpolationFactor();
    return utils::lerp(f, a, b);
}

Ogre::Quaternion State::interpolate(const Ogre::Quaternion& a, const Ogre::Quaternion& b) {
    const float f = calcInterpolationFactor();
    return Ogre::Quaternion::Slerp(f, a, b);
}

float State::calcInterpolationFactor() {
    const long long timestamp = utils::getTimestamp();
    const long long start = Game::previousUpdateTimestamp();
    const long long end = Game::currentUpdateTimestamp();

    const long long numerator = timestamp - start;
    const long long denominator = end - start;

    const float factor = denominator == 0
        ? 1.f
        : static_cast<float>(numerator) / static_cast<float>(denominator);

    return factor;
}

} // end namespace core