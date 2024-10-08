#pragma once

#include <thread>

using namespace std;

namespace core {

class NetworkLayer {
public:
    virtual ~NetworkLayer();

    void start();

    void stop();

    long long currentUpdateTimestamp() const { return m_currentUpdateTimestamp + MILLISECONDS_BETWEEN_TICKS; }
    long long previousUpdateTimestamp() const { return m_previousUpdateTimestamp + MILLISECONDS_BETWEEN_TICKS; }

protected:
    void virtual tick(float dt) = 0;

private:
    static constexpr int MILLISECONDS_BETWEEN_TICKS = 20; // 50 updates per second

    atomic<bool> m_running;
    thread m_tickThread;

    long long m_currentUpdateTimestamp = 0.0;
    long long m_previousUpdateTimestamp = 0.0;
};

} // end namespace core
