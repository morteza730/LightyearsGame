#pragma once

#include <weapon/shooter.hpp>
#include <weapon/bulletshooter.hpp>

namespace ly
{
    class FrontalWiper : public Shooter
    {
    public:
        FrontalWiper(Actor *owner,
                     float coolDownTime = 1.f,
                     const sf::Vector2f &localOffset = {0.f, 0.f},
                     float width = 60.f);

    private:
        virtual void increaseLevel(int amt) override;
        virtual void shootImp();
        float m_width;
        BulletShooter m_shooter1;
        BulletShooter m_shooter2;
        BulletShooter m_shooter3;
        BulletShooter m_shooter4;
        BulletShooter m_shooter5;
        BulletShooter m_shooter6;
    };
}