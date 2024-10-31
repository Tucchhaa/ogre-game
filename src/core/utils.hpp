#pragma once

#include <OGRE/OgreVector.h>
#include <btBulletDynamicsCommon.h>

using namespace std;

namespace core::utils {

#define STREAM_READ(stream, var) \
    stream.read(reinterpret_cast<char*>(&var), sizeof(var))

#define STREAM_WRITE(stream, var) \
    stream.write(reinterpret_cast<const char*>(&var), sizeof(var))

#define STREAM_WRITE_STRING(stream, var) \
    stream.write(reinterpret_cast<const char*>(&var), strlen(var)+1)

inline long long getTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto duration = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch());

    return duration.count();
}

inline Ogre::Vector3 lerp(float t, const Ogre::Vector3& a, const Ogre::Vector3& b) {
    return t >= 1 ? b : a + (b - a) * t;
}

inline Ogre::Vector3 convertVec3(const btVector3& position) {
    return Ogre::Vector3(position.x(), position.y(), position.z());
}

inline Ogre::Quaternion convertQuat(const btQuaternion& rotation) {
    return Ogre::Quaternion(rotation.w(), rotation.x(), rotation.y(), rotation.z());
}

inline bool isClientExecutable() {
    const char* isClientEnv = std::getenv("IS_CLIENT");
    return isClientEnv != nullptr && std::atoi(isClientEnv) == 1;
}

}
