#include "state.hpp"

#include "../game.hpp"
#include "../utils.hpp"
#include "../network_layer/network_layer.hpp"

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
    return Ogre::Quaternion::Slerp(calcInterpolationFactor(), a, b);
}

float State::calcInterpolationFactor() {
    const long long timestamp = utils::getTimestamp();
    const long long start = Game::networkLayer()->previousUpdateTimestamp();
    const long long end = Game::networkLayer()->currentUpdateTimestamp();

    const float result = static_cast<float>(timestamp - start) / static_cast<float>(end - start);

    return result;
}

} // end namespace core