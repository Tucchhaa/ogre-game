#pragma once

#include <OGRE/OgreVector.h>
#include <btBulletDynamicsCommon.h>
#include <chrono>
#include <arpa/inet.h>

namespace core::utils {

#define STREAM_READ(stream, var) \
    stream.read(reinterpret_cast<char*>(&var), sizeof(var))

#define STREAM_WRITE(stream, var) \
    stream.write(reinterpret_cast<const char*>(&var), sizeof(var))

#define STREAM_WRITE_STRING(stream, var) \
    stream.write(reinterpret_cast<const char*>(&var), strlen(var)+1)

inline long long getTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

    return duration.count();
}

inline Ogre::Vector3 lerp(float t, const Ogre::Vector3& a, const Ogre::Vector3& b) {
    return t >= 1 ? b : a + (b - a) * t;
}

inline Ogre::Vector3 convertVec3(const btVector3& position) {
    return Ogre::Vector3(position.x(), position.y(), position.z());
}

inline btVector3 convertVec3(const Ogre::Vector3& position) {
    return btVector3(position.x, position.y, position.z);
}

inline Ogre::Quaternion convertQuat(const btQuaternion& rotation) {
    return Ogre::Quaternion(rotation.w(), rotation.x(), rotation.y(), rotation.z());
}

inline btQuaternion convertQuat(const Ogre::Quaternion& rotation) {
    return btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w);
}

inline btVector3 rotateVec3(const btVector3& v, const btQuaternion& rotation) {
    btVector3 u(rotation.x(), rotation.y(), rotation.z());

    float s = rotation.w();

    auto result =
            2.0f * v.dot(u) * u
            + (s*s - u.dot(u)) * v
            + 2.0f * s * u.cross(v);

    return result;
}

inline float clamp(float a, float lower, float upper) {
    return std::min(upper, std::max(lower, a));
}

inline std::string convertIP(unsigned int host) {
    in_addr ip_addr{ host };

    auto result = std::string(inet_ntoa(ip_addr));

    return result;
}

}
