#include "network_layer_manager.hpp"

#include "network_layer.hpp"
#include "server.hpp"
#include "client.hpp"

namespace core {

void NetworkLayerManager::start(GameType gameType) {
    m_networkLayer = createNetworkLayer(gameType);

    m_networkLayer->start();
}

shared_ptr<Server> NetworkLayerManager::server() const {
    if(m_gameType == GameType::SinglePlayer || m_gameType == GameType::LANHost)
        return static_pointer_cast<Server>(m_networkLayer);

    return nullptr;
}

shared_ptr<Client> NetworkLayerManager::client() const {
    if(m_gameType == GameType::LANPeer)
        return static_pointer_cast<Client>(m_networkLayer);

    return nullptr;
}

shared_ptr<INetworkLayer> NetworkLayerManager::createNetworkLayer(GameType gameType) {
    m_gameType = gameType;

    if(m_networkLayer != nullptr) {
        m_networkLayer->stop();
        m_networkLayer.reset();
    }

    switch (m_gameType) {
        case GameType::SinglePlayer:
            return make_shared<Server>();

        case GameType::LANHost:
        case GameType::LANPeer:
        case GameType::None:
            break;
    }

    throw runtime_error("Not implemented");
}

} // end namespace core
