#pragma once

#include "enemy/enemySpaceship.hpp"
#include "weapon/bulletshooter.hpp"

namespace ly
{
    class UFO : public EnemySpaceship
    {
    public:
        UFO(World *world, const sf::Vector2f &velocity, const std::string &texture_path = "PNG/ufoBlue.png", float rotationVelocity = 40.f);
        virtual void tick(float deltaTime) override;

    private:
        virtual void shoot() override;
        float m_rotationVelocity;
        unique<BulletShooter> m_shooter1;
        unique<BulletShooter> m_shooter2;
        unique<BulletShooter> m_shooter3;
    };
}