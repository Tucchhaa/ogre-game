#pragma once
#include <thread>

using namespace std;

namespace core {

class INetworkLayer {
public:
    virtual ~INetworkLayer() = default;

    void start();

    void stop();

protected:
    void virtual tick(float dt) = 0;

private:
    static constexpr int MILLISECONDS_BETWEEN_TICKS = 20;

    atomic<bool> m_running;
    thread m_tickThread;
};

} // end namespace core
