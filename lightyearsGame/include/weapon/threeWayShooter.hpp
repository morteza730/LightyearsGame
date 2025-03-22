#pragma once

#include "weapon/shooter.hpp"
#include <sfml/Graphics.hpp>
#include "weapon/bulletshooter.hpp"

namespace ly
{
    class ThreeWayShooter: public Shooter
    {
    public:
        ThreeWayShooter(Actor *owner, float coolDownTime = 1.f, const sf::Vector2f &localOffset = {0.f, 0.f}, float rotationalOffset = 0);
        virtual void setCurrentLevel(int level) override;
        
    private:
        virtual void increaseLevel(int amt) override;
        virtual void shootImp();
        BulletShooter m_ShooterLeft;
        BulletShooter m_ShooterMiddle;
        BulletShooter m_ShooterRight;

        BulletShooter m_topLevelShooterRight;
        BulletShooter m_topLevelShooterLeft;
    };
}   