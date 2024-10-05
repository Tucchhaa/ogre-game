#pragma once

#include <string>
#include <map>
#include <any>

using namespace std;

namespace core {

#define STATE_PROP(type, name)    \
    public:                       \
    void name(type value) {       \
        m_changes[#name] = value; \
    }                             \
    type name() {                 \
        return m_##name;          \
    }                             \
    private:                      \
    type m_##name

// TODO: this is temporary solution. We want to avoid code duplication
#define STATE_PROP_SETTER(type, name)       \
    m_setters[#name] = [this](any value) {  \
        this->name = any_cast<type>(value); \
    }

class State {
public:
    virtual ~State() = default;

    void applyChanges() {
        for(const auto& [key, value]: m_changes) {
            m_setters[key](value);
        }

        m_changes.clear();
    }

protected:
    map<string, any> m_changes;
    map<string, function<void(any)>> m_setters;

    void virtual registerSetters() = 0;
};

}
