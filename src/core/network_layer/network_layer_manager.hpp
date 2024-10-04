#pragma once

#include "network_layer.hpp"

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

    void init(GameType gameType);

    void start() const;

private:
    GameType m_gameType = GameType::None;

    shared_ptr<INetworkLayer> m_networkLayer;
};

} // end namespace core
