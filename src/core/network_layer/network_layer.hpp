#pragma once
#include <thread>

using namespace std;

namespace core {

class INetworkLayer {
public:
    virtual ~INetworkLayer() = default;

    void start() {
        m_running.store(true);

        m_tickThread = thread([this]() {
            constexpr float dt = MILLISECONDS_BETWEEN_TICKS/1000.;
            constexpr auto interval = chrono::milliseconds(MILLISECONDS_BETWEEN_TICKS);

            auto nextTick = std::chrono::steady_clock::now();

            while(m_running.load()) {
                auto now = std::chrono::steady_clock::now();

                if(now >= nextTick) {
                    tick(dt);

                    nextTick = now + interval;
                }

                this_thread::sleep_until(nextTick);
            }
        });
    }

    void stop() {
        m_running.store(false);

        if (m_tickThread.joinable()) {
            m_tickThread.join();
        }
    }

protected:
    void virtual tick(float dt) = 0;

private:
    static constexpr int MILLISECONDS_BETWEEN_TICKS = 20;

    atomic<bool> m_running;
    thread m_tickThread;
};

} // end namespace core
