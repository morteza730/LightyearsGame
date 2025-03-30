#pragma once

#include "enemy/enemySpaceship.hpp"
#include "weapon/BulletShooter.hpp"

namespace ly
{
    class TwinBlade : public EnemySpaceship
    {
        public:
            TwinBlade(World *world,const std::string &texture_path="PNG/Enemies/enemyBlack1.png",const sf::Vector2f &velocity = {0.f,120.f});
            virtual void tick(float deltaTime) override;

        private:
            virtual void shoot() override;
            unique<BulletShooter> m_shooterLeft;
            unique<BulletShooter> m_shooterRight;
    };
}