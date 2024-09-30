#pragma once

#include <btBulletDynamicsCommon.h>

#include "OgreManualObject.h"

namespace core::debug {

class ColliderDrawer : public btIDebugDraw {
public:
    ColliderDrawer();

    ~ColliderDrawer() override;

    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;

    void render();

    int getDebugMode() const override { return DBG_DrawWireframe; }

    // ===
    // Unused methods
    // ===
    void reportErrorWarning(const char* warningString) override {}

    void draw3dText(const btVector3& location, const char* textString) override {}

    void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override {}

    void setDebugMode(int debugMode) override {}

private:
    Ogre::ManualObject* m_manualObject = nullptr;
    Ogre::MaterialPtr m_material;

    std::vector<Ogre::Vector3> m_lines;

    static Ogre::MaterialPtr createMaterial();

    static Ogre::ManualObject* createManualObject();
};

} // end namespace core::debug
