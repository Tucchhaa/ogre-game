#include "network_layer.hpp"

#include "../utils.hpp"

namespace core {

NetworkLayer::~NetworkLayer() {
    stop();
}

void NetworkLayer::start() {
    m_running.store(true);

    m_tickThread = thread([this]() {
        constexpr float dt = MILLISECONDS_BETWEEN_TICKS/1000.;
        constexpr auto interval = chrono::milliseconds(MILLISECONDS_BETWEEN_TICKS);

        auto nextTick = std::chrono::steady_clock::now();
        m_currentUpdateTimestamp = utils::getTimestamp();

        while(m_running.load()) {
            auto now = std::chrono::steady_clock::now();

            m_previousUpdateTimestamp = m_currentUpdateTimestamp;
            m_currentUpdateTimestamp = utils::getTimestamp();

            if(now >= nextTick) {
                tick(dt);

                nextTick = now + interval;
            }

            this_thread::sleep_until(nextTick);
        }
    });
}

void NetworkLayer::stop() {
    m_running.store(false);

    if (m_tickThread.joinable()) {
        m_tickThread.join();
    }
}


} // end namespace core