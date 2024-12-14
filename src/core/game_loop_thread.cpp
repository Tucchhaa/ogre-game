#include "game_loop_thread.hpp"

#include "game.hpp"
#include "utils.hpp"

using namespace std;

namespace core {

long long GameLoopThread::currentUpdateTimestamp() {
    std::lock_guard _(updateTimestampMutex);
    return m_currentUpdateTimestamp;
}

long long GameLoopThread::previousUpdateTimestamp() {
    std::lock_guard _(updateTimestampMutex);
    return m_previousUpdateTimestamp;
}

void GameLoopThread::start() {
    m_running.store(true);

    m_tickThread = thread([this]() {
        constexpr float dt = MILLISECONDS_BETWEEN_TICKS/1000.;
        constexpr auto interval = chrono::milliseconds(MILLISECONDS_BETWEEN_TICKS);

        auto nextTick = std::chrono::steady_clock::now();

        {
            lock_guard _(updateTimestampMutex);
            m_currentUpdateTimestamp = utils::getTimestamp();
        }

        while(m_running.load()) {
            auto now = std::chrono::steady_clock::now();

            {
                lock_guard _(updateTimestampMutex);
                m_previousUpdateTimestamp = m_currentUpdateTimestamp;
                m_currentUpdateTimestamp = utils::getTimestamp() + MILLISECONDS_BETWEEN_TICKS;
            }

            if(now >= nextTick) {
                tick(dt);

                nextTick = now + interval;
            }

            this_thread::sleep_until(nextTick);
        }
    });
}

void GameLoopThread::stop() {
    if(m_running.load() == false) {
        return;
    }

    m_running.store(false);

    if (m_tickThread.joinable()) {
        m_tickThread.join();
    }
}

void SinglePlayer::tick(float dt) {
    Game::physics()->stepSimulationFixed(dt);

    GameEventListener::callFixedUpdate(dt);
}

} // end namespace core
