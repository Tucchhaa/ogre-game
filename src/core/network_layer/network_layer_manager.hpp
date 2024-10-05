#pragma once

#include <memory>

using namespace std;

namespace core {

class Server;
class Client;
class INetworkLayer;

enum class GameType {
    None,
    SinglePlayer,
    LANHost,
    LANPeer
};

class NetworkLayerManager {
public:
    NetworkLayerManager() = default;

    void start(GameType gameType);

    shared_ptr<Server> server() const;

    shared_ptr<Client> client() const;

private:
    GameType m_gameType = GameType::None;

    shared_ptr<INetworkLayer> m_networkLayer;

    shared_ptr<INetworkLayer> createNetworkLayer(GameType gameType);
};

} // end namespace core
