#include "network_manager.hpp"

#include "network_base.hpp"
#include "lan_scanner.hpp"
#include "server.hpp"
#include "client.hpp"

using namespace std;

namespace core {

NetworkManager::NetworkManager() {
    enet_initialize();

    m_LANScanner = make_shared<LANScanner>();
}

NetworkManager::~NetworkManager() {
    enet_deinitialize();
}

void NetworkManager::searchLANServers() {
    m_LANServers = m_LANScanner->scan();
}

void NetworkManager::initClient() {
    m_peer = createPeer(NetworkType::LANPeer);
}

void NetworkManager::initServer() {
    m_peer = createPeer(NetworkType::LANPeer);
}

void NetworkManager::start() const {
    m_peer->start();
}

void NetworkManager::stop() {
    if(m_peer != nullptr) {
        m_peer->stop();
        m_peer.reset();
    }
}

shared_ptr<Server> NetworkManager::server() const {
    if(m_networkType == NetworkType::LANHost)
        return static_pointer_cast<Server>(m_peer);

    return nullptr;
}

shared_ptr<Client> NetworkManager::client() const {
    if(m_networkType == NetworkType::LANPeer)
        return static_pointer_cast<Client>(m_peer);

    return nullptr;
}

std::shared_ptr<NetworkBase> NetworkManager::createPeer(NetworkType networkType) {
    if(m_peer != nullptr) {
        throw runtime_error("Network was not stopped. Stop it before starting new game.");
    }

    m_networkType = networkType;
    std::shared_ptr<NetworkBase> peer;

    switch (networkType) {
        case NetworkType::LANHost:
            peer = make_shared<Server>();
            break;
        case NetworkType::LANPeer:
            peer = make_shared<Client>();
            break;
        default:
            throw runtime_error("Incorrect PeerType can not create peer");
    }

    peer->init();

    return peer;
}

} // end namespace core
