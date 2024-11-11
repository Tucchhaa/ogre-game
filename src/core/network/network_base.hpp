#pragma once

#include <thread>
#include <atomic>
#include <mutex>
#include <enet/enet.h>

namespace core {

enum class HostType {
    Client,
    Server,
};

/*
 * Base class for Client and Server
 */
class NetworkBase {
public:
    explicit NetworkBase(HostType hostType): m_hostType(hostType) {}
    virtual ~NetworkBase();

    /**
     * Timestamp of the most recent update.
     */
    long long currentUpdateTimestamp();

    /**
     * The timestamp of the previous update.
     */
    long long previousUpdateTimestamp();

    virtual void init();

    /**
     * Start logic thread
     */
    virtual void start();

    /**
     * Stop logic thread
     */
    virtual void stop();

   protected:
    static constexpr enet_uint8 UNRELIABLE_CHANNEL_ID = 0;
    static constexpr enet_uint8 RELIABLE_CHANNEL_ID = 1;

    ENetHost* m_host = nullptr;

    virtual void tick(float dt) {}

    /**
     * If server, then called when a client connects to the server.
     * If client, then called when it connects to a server.
     */
    virtual void onConnected() {}

    /**
     * If server, then called when a client disconnects from the server.
     * If client, then called when the client was disconnected from the server.
     */
    virtual void onDisconnected() {}

    /**
     * If client, then called when a message from the server was received.
     * If server, then called when a message from a client was received.
     */
    virtual void onMessage(std::istream& stream) {}

    static ENetPacket* createPacket(const std::ostringstream &stream, enet_uint8 channel_id);

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

    HostType m_hostType;

    ENetHost* createHost() const;

    void handleEnetEvent();
};

} // end namespace core
