#pragma once

#include "base.hpp"
#include "core/scene/custom_scene_node.hpp"

namespace game {

class Fighter : public BaseStarFighter {
public:
    Fighter();

protected:
    void primaryAttack(float dt) override;

    void secondaryAttack(float dt) override;

    void fixedUpdate(float dt) override;

private:
    struct BulletInfo {
        core::CustomSceneNode* node;
        core::Collider* collider;
    };

    std::vector<BulletInfo> m_bullets;

    const std::vector<Ogre::Vector3> m_shootingPositions = {
        Ogre::Vector3(-7, 0, -8),
        Ogre::Vector3(7, 0, -8),
        Ogre::Vector3(-1, -1, -15),
        Ogre::Vector3(1, -1, -15)
    };

    const int m_ammoPerShoot = m_shootingPositions.size();
    const int m_maxAmmo = 400;
    const float m_bulletSpeed = 1000;
    const float m_bulletMass = 0.000001;
    const int m_delayPerShoot = 100;
    const int m_delayPerReload = 100;

    int m_bulletIndex = 0;
    int m_ammo = m_maxAmmo;
    long long m_lastPrimaryAttackTimestamp = 0;
    long long m_lastPrimaryReloadTimestamp = 0;
};

} // end namespace game