#pragma once

#include <string>
#include <map>
#include <any>

using namespace std;

namespace core {

#define STATE_PROP(type, name)    \
    public:                       \
    void name(type value) {       \
        m_##name = value;         \
        m_changes[#name] = value; \
    }                             \
    type name() {                 \
        return m_##name;          \
    }                             \
    private:                      \
    type m_##name

/**
 * Stores a state of a MovableObject.
 * Changes of state must be implemented in fixedUpdate
 * Note: not concurrency safe, use only in fixedUpdate
 */
class State {
public:
    State() = default;
    virtual ~State() = default;

    map<string, any> popChanges() {
        auto value = m_changes;

        m_changes.clear();

        return value;
    }

protected:
    map<string, any> m_changes;
};

} // end namespace core
