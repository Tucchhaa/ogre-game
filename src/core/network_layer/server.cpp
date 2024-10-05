#include "server.hpp"

#include <queue>

#include "../game.hpp"
#include "../objects/base_movable_object.hpp"

void core::Server::tick(float dt) {
    simulatePhysics(dt);
    callFixedUpdate(dt);
}

void core::Server::simulatePhysics(float dt) {
    Game::physics()->stepSimulationFixed(dt);
}

void core::Server::callFixedUpdate(float dt) {
    queue<Ogre::SceneNode*> q;
    q.push(Game::sceneManager()->getRootSceneNode());

    // TODO: consider iterating through callbacks, instead of the scene tree
    while(!q.empty()) {
        const auto node = q.front();
        q.pop();

        for(auto child: node->getChildren()) {
            q.push(static_cast<Ogre::SceneNode*>(child));
        }

        for(const auto object: node->getAttachedObjects()) {
            auto binding =  object->getUserObjectBindings().getUserAny();

            if(binding.has_value() == false)
                continue;

            auto* casted = Ogre::any_cast<BaseMovableObject*>(binding);

            casted->fixedUpdate(dt);

            // Here server could store all changes and send them to clients

            if(casted->state() != nullptr) {
                casted->state()->applyChanges();
            }
        }
    }
}
