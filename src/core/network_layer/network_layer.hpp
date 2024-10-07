#pragma once

#include <thread>

using namespace std;

namespace core {

class NetworkLayer {
public:
    virtual ~NetworkLayer();

    void start();

    void stop();

    long long currentUpdateTimestamp() const { return m_currentUpdateTimestamp; }
    long long previousUpdateTimestamp() const { return m_previousUpdateTimestamp; }

protected:
    void virtual tick(float dt) = 0;

private:
    static constexpr int MILLISECONDS_BETWEEN_TICKS = 20;

    atomic<bool> m_running;
    thread m_tickThread;

    long long m_currentUpdateTimestamp = 0.0;
    long long m_previousUpdateTimestamp = 0.0;
};

} // end namespace core
