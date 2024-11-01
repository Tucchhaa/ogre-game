#include "network_layer_manager.hpp"

#include "network_layer.hpp"
#include "lan_scanner.hpp"
#include "server.hpp"
#include "client.hpp"

using namespace std;

namespace core {

NetworkLayerManager::NetworkLayerManager() {
    enet_initialize();

    m_LANScanner = make_shared<LANScanner>();
}

NetworkLayerManager::~NetworkLayerManager() {
    enet_deinitialize();
}

// TODO: make it a return a list of found games, so later it will be shown as a list of found games
bool NetworkLayerManager::searchLANGames() {
    m_LANServers = m_LANScanner->scan();

    return !m_LANServers.empty();
}

void NetworkLayerManager::initNetworkLayer(NetworkType gameType) {
    m_networkLayer = createNetworkLayer(gameType);
    m_networkLayer->init();
}

void NetworkLayerManager::start() const {
    if(m_networkType == NetworkType::None) {
        throw runtime_error("Wrong game type: can not start");
    }

    m_networkLayer->start();
}

void NetworkLayerManager::stop() {
    if(m_networkLayer != nullptr) {
        m_networkLayer->stop();
        m_networkLayer.reset();
    }
}

shared_ptr<Server> NetworkLayerManager::server() const {
    if(m_networkType == NetworkType::SinglePlayer || m_networkType == NetworkType::LANHost)
        return static_pointer_cast<Server>(m_networkLayer);

    return nullptr;
}

shared_ptr<Client> NetworkLayerManager::client() const {
    if(NetworkType::LANPeer == m_networkType)
        return static_pointer_cast<Client>(m_networkLayer);

    return nullptr;
}

shared_ptr<NetworkLayer> NetworkLayerManager::createNetworkLayer(NetworkType gameType) {
    m_networkType = gameType;

    stop();

    switch (m_networkType) {
        case NetworkType::SinglePlayer:
        case NetworkType::LANHost:
            return make_shared<Server>();

        case NetworkType::LANPeer:
            if(m_LANServers.empty()) {
                throw runtime_error("No LAN servers found. Can not join");
            }

            // TODO: connect not to the first discovered, but to the selected by the user
            return make_shared<Client>(m_LANServers[0]);
        case NetworkType::None:
            break;
    }

    throw runtime_error("Not implemented");
}

} // end namespace core
