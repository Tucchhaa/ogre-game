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

    const int m_maxAmmo = 100;
    const float m_reloadAmmoPerSecond = 10;
    const float m_bulletSpeed = 500;
    const long long m_delayPerShootMs = 100;

    int m_bulletIndex = 0;
    long long m_lastPrimaryAttackTimestamp = 0;
    float m_ammo = (float)m_maxAmmo;
};

} // end namespace game