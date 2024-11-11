#include "transform_state.hpp"

#include "../../utils.hpp"

using namespace std;

namespace core {

void TransformState::setValues(const btVector3& position, const btQuaternion& rotation) {
    unique_lock _(m_mutex);

    // use unsafe functions because mutex is already locked
    set_position_unsafe(utils::convertVec3(position));
    set_rotation_unsafe(utils::convertQuat(rotation));
}

void TransformState::getValues(Ogre::Vector3& position, Ogre::Quaternion& rotation) {
    shared_lock _(m_mutex);

    // use unsafe functions because mutex is already locked
    position = interpolate_position_unsafe();
    rotation = interpolate_rotation_unsafe();
}

void TransformState::getValues(btVector3& position, btQuaternion& rotation) {
    Ogre::Vector3 ogrePosition;
    Ogre::Quaternion ogreRotation;

    getValues(ogrePosition, ogreRotation);

    position = utils::convertVec3(ogrePosition);
    rotation = utils::convertQuat(ogreRotation);
}

void TransformState::resetValues(const btVector3& position, const btQuaternion& rotation) {
    resetValues(utils::convertVec3(position), utils::convertQuat(rotation));
}

void TransformState::resetValues(const Ogre::Vector3& position, const Ogre::Quaternion& rotation) {
    unique_lock _(m_mutex);

    m_position = m_previous_position = position;
    m_rotation = m_previous_rotation = rotation;
}

void TransformState::serialize(std::ostream& stream) {
    shared_lock _(m_mutex);

    STREAM_WRITE(stream, m_position);
    STREAM_WRITE(stream, m_rotation);
}

void TransformState::deserialize(std::istream& stream) {
    Ogre::Vector3 position;
    Ogre::Quaternion rotation;

    STREAM_READ(stream, position);
    STREAM_READ(stream, rotation);

    unique_lock _(m_mutex);

    // use unsafe functions because mutex is already locked
    set_position_unsafe(position);
    set_rotation_unsafe(rotation);
}

} // end namespace core