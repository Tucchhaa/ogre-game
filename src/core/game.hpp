#pragma once

#include <OGRE/Ogre.h>
#include <OgreApplicationContext.h>

#include "input.hpp"

using namespace std;

namespace core {

class Scene;

class Game {
public:
    static Game& instance() {
        static Game _instance;
        return _instance;
    }

    // To prevent copying
    Game(Game const&) = delete;
    // To prevent copying
    void operator=(Game const&) = delete;

    Game() = default;

    void configure();

    void init();

    void start() const;

    // ===
    // Static getters
    // ===
    static OgreBites::ApplicationContext* appContext() { return instance().m_ctx; }
    static Ogre::Root* root() { return instance().m_ctx->getRoot(); }
    static Ogre::SceneManager* sceneManager() { return instance().m_sceneManager; }
    static shared_ptr<Input> input() { return instance().m_input; }
    static shared_ptr<Scene> scene() { return instance().m_scene; }

    void scene(const shared_ptr<Scene>& scene) { m_scene = scene; }

private:
    OgreBites::ApplicationContext* m_ctx = nullptr;
    Ogre::SceneManager* m_sceneManager = nullptr;

    shared_ptr<Input> m_input;
    shared_ptr<Scene> m_scene;
};

} // end namespace core