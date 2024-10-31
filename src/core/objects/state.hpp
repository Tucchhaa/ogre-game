#pragma once

#include <string>
#include <map>
#include <any>
#include <istream>
#include <ostream>
#include <shared_mutex>

#include <OGRE/OgreVector.h>

using namespace std;

namespace core {

/**
 * Stores a state of a MovableObject.
 * Note: Concurrency safe, can be used both in fixedUpdate and frameRenderingQueued
 */
class State {
public:
    State() = default;
    virtual ~State() = default;

    map<string, any> popChanges();

    virtual void serialize(std::ostream& stream) { }
    virtual void deserialize(std::istream& stream) { }

protected:
    map<string, any> m_changes;
    mutable shared_mutex m_mutex;

    static Ogre::Vector3 interpolate(const Ogre::Vector3& a, const Ogre::Vector3& b);
    static Ogre::Quaternion interpolate(const Ogre::Quaternion& a, const Ogre::Quaternion& b);

private:
    static float calcInterpolationFactor();
};

/**
 * Defines props getter and setter
 * @param type type of the property: int, string, Vec3...
 */
#define STATE_PROP(type, name)                    \
    public:                                       \
    void name(const type& value) {                \
        unique_lock _(m_mutex);                   \
        set_##name##_unsafe(value);               \
    }                                             \
    type name() const {                           \
        shared_lock _(m_mutex);                   \
        return m_##name;                          \
    }                                             \
                                                  \
    protected:                                    \
    void set_##name##_unsafe(const type& value) { \
        m_previous_##name = m_##name;             \
        m_##name = value;                         \
        m_changes[#name] = value;                 \
    }                                             \
    type m_previous_##name;                       \
    type m_##name

/**
 * Defines everything that @link STATE_PROP defines and
 * interpolation function, which returns an interpolated value
 * of last two values of the property.
 * @param type type of the property: Vector3, Quaternion
 */
#define STATE_INTERPOLATABLE_PROP(type, name)                   \
    public:                                                     \
    type interpolate_##name() {                                 \
        shared_lock _(m_mutex);                                 \
        return interpolate_##name##_unsafe();                   \
    }                                                           \
    type interpolate_##name##_unsafe() {                        \
        return State::interpolate(m_previous_##name, m_##name); \
    }                                                           \
    STATE_PROP(type, name)

} // end namespace core
