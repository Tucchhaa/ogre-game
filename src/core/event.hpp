#pragma once

#include <functional>
#include <map>
#include <mutex>

using namespace std;

namespace core {

template<typename TCallback>
class TemplateEvent {
public:
    using callback_type = function<TCallback>;

    virtual ~TemplateEvent() = default;
    TemplateEvent() = default;

    int subscribe(const callback_type& callback) {
        lock_guard _(m_callbacks_mutex);

        const int id = generateCallbackID();

        m_callbacks[id] = callback;

        return id;
    }

    void unsubscribe(int id) {
        lock_guard _(m_callbacks_mutex);

        m_callbacks.erase(id);
    }

    virtual void fire() = 0;

protected:
    mutex m_callbacks_mutex;
    map<int, callback_type> m_callbacks;

private:
    static int generateCallbackID() {
        static int lastCallbackID = 0;
        return ++lastCallbackID;
    }
};

class Event : public TemplateEvent<void()> {
public:
    void fire() override {
        lock_guard _(m_callbacks_mutex);

        for(const auto& [id, callback] : m_callbacks)
            callback();
    }
};

} // end namespace core
