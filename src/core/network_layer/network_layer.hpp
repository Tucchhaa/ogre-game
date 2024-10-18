#pragma once

#include <thread>

using namespace std;

namespace core {

class NetworkLayer {
public:
    virtual ~NetworkLayer();

    void start();

    void stop();

    /**
     * Timestamp of the most recent update.
     */
    long long currentUpdateTimestamp() {
        lock_guard _(updateTimestampMutex);
        return m_currentUpdateTimestamp;
    }

    /**
     * The timestamp of the previous update.
     */
    long long previousUpdateTimestamp() {
        lock_guard _(updateTimestampMutex);
        return m_previousUpdateTimestamp;
    }

protected:
    void virtual tick(float dt) = 0;

private:
    static constexpr int MILLISECONDS_BETWEEN_TICKS = 20; // 50 updates per second

    atomic<bool> m_running;
    thread m_tickThread;
    // mutex for reading/writing @m_currentUpdateTimestamp, @m_previousUpdateTimestamp
    mutex updateTimestampMutex;

    // Important note: this is accessed from multiple threads.
    long long m_currentUpdateTimestamp = 0;
    // Important note: this is accessed from multiple threads.
    long long m_previousUpdateTimestamp = 0;

};

} // end namespace core
