#pragma once

#include <memory>

#include "client.hpp"
#include "server.hpp"

using namespace std;

namespace core {

enum class GameType {
    None,
    SinglePlayer,
    LANHost,
    LANPeer
};

class NetworkLayerManager {
public:
    NetworkLayerManager() = default;

    void init(GameType gameType) {
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

    void start() {
        m_networkLayer->start();
    }

private:
    GameType m_gameType = GameType::None;

    shared_ptr<INetworkLayer> m_networkLayer;
};

} // end namespace core
