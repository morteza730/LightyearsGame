#pragma once

#include "shooter.hpp"
#include <sfml/System.hpp>

namespace ly
{
    class BulletShooter : public Shooter
    {
    public:
        BulletShooter(Actor *owner, float coolDownTime = 1.f, const sf::Vector2f &localPositionOffset = {0.f, 0.f}, float localRotationOffset = 0);
        virtual bool isOnCoolDown() const override;

    private:
        virtual void shootImp() override;
        sf::Clock m_coolDownTimer;
        float m_coolDownTime;
        sf::Vector2f m_localPositionOffset;
        float m_localRotationOffset;
    };
}