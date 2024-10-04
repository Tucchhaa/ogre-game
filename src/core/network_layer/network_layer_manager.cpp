#include "network_layer_manager.hpp"

#include "server.hpp"

void core::NetworkLayerManager::init(GameType gameType) {
    m_gameType = gameType;

    if(m_networkLayer != nullptr) {
        m_networkLayer->stop();
        m_networkLayer.reset();
    }

    switch (m_gameType) {
        case GameType::SinglePlayer:
            m_networkLayer = make_shared<Server>();
            break;

        case GameType::LANHost:
        case GameType::LANPeer:
            throw runtime_error("Not implemented");

        case GameType::None:
            break;
    }
}

void core::NetworkLayerManager::start() const {
    m_networkLayer->start();
}
