#pragma once

#include <btBulletDynamicsCommon.h>

#include "state.hpp"

namespace core {

/**
 * Synchronizes colliders position and rotation between render and logic threads
 */
class TransformState: public State {
    STATE_INTERPOLATABLE_PROP(Ogre::Vector3, position);
    STATE_INTERPOLATABLE_PROP(Ogre::Quaternion, rotation);

public:
    void setValues(const btVector3& position, const btQuaternion& rotation);

    void getValues(Ogre::Vector3& position, Ogre::Quaternion& rotation);
    void getValues(btVector3& position, btQuaternion& rotation);

    void resetValues(const btVector3& position, const btQuaternion& rotation);
    void resetValues(const Ogre::Vector3& position, const Ogre::Quaternion& rotation);

    void serialize(std::ostream& stream) override;

    void deserialize(std::istream& stream) override;
};

} // end namespace core
