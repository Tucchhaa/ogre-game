#pragma once

#include <functional>
#include <map>
#include <mutex>

namespace core {

template<typename TCallback>
class TemplateEvent {
public:
    using callback_type = std::function<TCallback>;

    virtual ~TemplateEvent() = default;
    TemplateEvent() = default;

    int subscribe(const callback_type& callback) {
        std::lock_guard _(m_callbacks_mutex);

        const int id = generateCallbackID();

        m_callbacks[id] = callback;

        return id;
    }

    void unsubscribe(int id) {
        std::lock_guard _(m_callbacks_mutex);

        m_callbacks.erase(id);
    }

    virtual void fire() = 0;

protected:
    std::mutex m_callbacks_mutex;
    std::map<int, callback_type> m_callbacks;

private:
    static int generateCallbackID() {
        static int lastCallbackID = 0;
        return ++lastCallbackID;
    }
};

class Event : public TemplateEvent<void()> {
public:
    void fire() override {
        std::lock_guard _(m_callbacks_mutex);

        for(const auto& [id, callback] : m_callbacks)
            callback();
    }
};

} // end namespace core
