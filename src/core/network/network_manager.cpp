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

long long NetworkManager::previousUpdateTimestamp() const {
    return m_peer == nullptr ? 0 : m_peer->previousUpdateTimestamp();
}

long long NetworkManager::currentUpdateTimestamp() const {
    return m_peer == nullptr ? 0 : m_peer->currentUpdateTimestamp();
}

// TODO: make it a return a list of found games, so later it will be shown as a list of found games
bool NetworkManager::searchLANGames() {
    m_LANServers = m_LANScanner->scan();

    return !m_LANServers.empty();
}

void NetworkManager::initClient() {
    m_peerType = PeerType::LANPeer;
    m_peer = createClient();
}

void NetworkManager::initServer() {
    m_peerType = PeerType::LANHost;
    m_peer = createServer();
}

void NetworkManager::initSinglePlayer() {
    m_peerType = PeerType::SinglePlayer;
    m_peer = createServer();
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
    if(m_peerType == PeerType::SinglePlayer || m_peerType == PeerType::LANHost)
        return static_pointer_cast<Server>(m_peer);

    return nullptr;
}

shared_ptr<Client> NetworkManager::client() const {
    if(PeerType::LANPeer == m_peerType)
        return static_pointer_cast<Client>(m_peer);

    return nullptr;
}

std::shared_ptr<NetworkBase> NetworkManager::createServer() const {
    if(m_peer != nullptr) {
        throw runtime_error("Network was not stopped. Stop it before starting new game.");
    }

    auto peer = make_shared<Server>();
    peer->init();

    return peer;
}

std::shared_ptr<NetworkBase> NetworkManager::createClient() {
    if(m_peer != nullptr) {
        throw runtime_error("Network was not stopped. Stop it before starting new game.");
    }

    if(m_LANServers.empty()) {
        throw runtime_error("No LAN servers found. Can not join");
    }

    // TODO: connect not to the first discovered, but to the selected by the user
    auto peer = make_shared<Client>(m_LANServers[0]);
    peer->init();

    return peer;
}

} // end namespace core
