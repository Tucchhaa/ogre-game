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
    const Ogre::Vector3 m_shootingPos1 = Ogre::Vector3(0, 0, -10);
    const Ogre::Vector3 m_shootingPos2 = Ogre::Vector3::ZERO;
    const Ogre::Vector3 m_shootingPos3 = Ogre::Vector3::ZERO;
    const Ogre::Vector3 m_shootingPos4 = Ogre::Vector3::ZERO;

    const int m_maxAmmo = 50;
    const float m_bulletSpeed = 500;
    const float m_bulletMass = 0.000001;
    const int m_delayPerShoot = 100;
    const int m_delayPerReload = 200;

    int m_bulletIndex = 0;
    int m_ammo = m_maxAmmo;
    long long m_lastPrimaryAttackTimestamp = 0;
    long long m_lastPrimaryReloadTimestamp = 0;
};

} // end namespace game