#pragma once

#include <atomic>
#include <thread>

namespace core {

class GameLoopThread {
public:
    enum class GameLoopType {
        SinglePlayer,
        LANMultiplayerHost,
        LANMultiplayerPeer
    };

    virtual ~GameLoopThread() = default;

    virtual GameLoopType type() const = 0;

    /**
     * Timestamp of the most recent update.
     */
    long long currentUpdateTimestamp();

    /**
     * The timestamp of the previous update.
     */
    long long previousUpdateTimestamp();

    /**
     * Start logic thread
     */
    virtual void start();

    /**
     * Stop logic thread
     */
    virtual void stop();

protected:
    /**
     * Called at fixed rate
     * @param dt delta time between ticks
     */
    virtual void tick(float dt) = 0;

private:
    static constexpr int MILLISECONDS_BETWEEN_TICKS = 20; // 50 updates per second

    std::atomic<bool> m_running{false};
    std::thread m_tickThread;
    // mutex for reading/writing @m_currentUpdateTimestamp, @m_previousUpdateTimestamp
    std::mutex updateTimestampMutex;

    // Important note: this is accessed from multiple threads.
    long long m_currentUpdateTimestamp = 0;
    // Important note: this is accessed from multiple threads.
    long long m_previousUpdateTimestamp = 0;
};

class SinglePlayer : public GameLoopThread {
protected:
    void tick(float dt) override;

    GameLoopType type() const override { return GameLoopType::SinglePlayer; }
};

} // end namespace core
