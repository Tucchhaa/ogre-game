#pragma once

#include <functional>
#include <mutex>

namespace core {

template<typename... Args>
class Event {
public:
    using Listener = std::function<void(Args...)>;

    /// Subscribe a new listener to the event
    /// Returns a unique identifier for the listener
    size_t subscribe(const Listener& listener) {
        size_t id = currentId.fetch_add(1, std::memory_order_relaxed);
        std::lock_guard lock(m_mutex);

        listeners.emplace_back(id, listener);

        return id;
    }

    // Overload to subscribe member functions
    template <typename T>
    size_t subscribe(T* instance, void (T::*memberFunc)(Args...)) {
        Listener listener = [=](Args... args) {
            (instance->*memberFunc)(args...);
        };
        return subscribe(listener);
    }

    // Overload to subscribe member functions
    template <typename T>
    size_t subscribe(T* instance, void (T::*memberFunc)(Args...) const) {
        Listener listener = [=](Args... args) {
            (instance->*memberFunc)(args...);
        };
        return subscribe(listener);
    }

    void unsubscribe(size_t id) {
        std::lock_guard lock(m_mutex);

        auto it = find_if(
            listeners.begin(), listeners.end(),
            [id](auto item) { return item.id == id; }
        );

        if(it != listeners.end()) {
            listeners.erase(it);
        }
    }


    void invoke(Args... args) const {
        std::vector<Listener> listenersCopy;
        {
            std::lock_guard lock(m_mutex);
            // Copy the listeners to avoid holding the lock during invocation
            for (const auto& item : listeners) {
                listenersCopy.emplace_back(item.listener);
            }
        }

        for (const auto& listener : listenersCopy) {
            listener(args...);
        }
    }

    void clear() {
        std::lock_guard lock(m_mutex);
        listeners.clear();
    }

private:
    struct ListenerItem {
        size_t id;
        Listener listener;

        ListenerItem(size_t listenerId, const Listener& lst) : id(listenerId), listener(lst) {}
    };

    mutable std::mutex m_mutex;
    std::vector<ListenerItem> listeners;
    std::atomic<size_t> currentId = 0;
};

} // end namespace core
