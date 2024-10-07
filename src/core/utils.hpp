#pragma once

#include <chrono>
#include <OGRE/OgreVector.h>

using namespace std;

namespace core::utils {

inline long long getTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto duration = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch());

    return duration.count();
}

inline Ogre::Vector3 lerp(float t, const Ogre::Vector3& a, const Ogre::Vector3& b) {
    return t >= 1 ? a : a + (b - a) * t;
}

}
