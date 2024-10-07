#pragma once

#include <memory>

using namespace std;

namespace core {

class Server;
class Client;
class NetworkLayer;

enum class GameType {
    None,
    SinglePlayer,
    LANHost,
    LANPeer
};

class NetworkLayerManager {
public:
    NetworkLayerManager() = default;

    void initNetworkLayer(GameType gameType);
    void start() const;
    void stop();

    shared_ptr<NetworkLayer> networkLayer() const { return m_networkLayer; }
    shared_ptr<Server> server() const;
    shared_ptr<Client> client() const;

private:
    GameType m_gameType = GameType::None;

    shared_ptr<NetworkLayer> m_networkLayer;

    shared_ptr<NetworkLayer> createNetworkLayer(GameType gameType);
};

} // end namespace core
