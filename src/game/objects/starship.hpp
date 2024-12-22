#pragma once

#include "OgreSceneNode.h"

namespace core {
class CustomSceneNode;
}

namespace game {

class Starship {
public:
    Starship(Ogre::SceneNode* node): m_node(node) {}

    Ogre::SceneNode* node() const { return m_node; }

private:
    Ogre::SceneNode* m_node;

    int m_healthPoints = 10000;
};

}
