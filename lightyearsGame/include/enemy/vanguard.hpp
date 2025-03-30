#pragma once

#include "enemy/enemySpaceship.hpp"
#include "weapon/BulletShooter.hpp"

namespace ly
{
    class Vanguard: public EnemySpaceship
    {
        public:
            Vanguard(World *world,const std::string &texture_path="PNG/Enemies/enemyBlue3.png",const sf::Vector2f &velocity = {0.f,150.f});
            virtual void tick(float deltaTime) override;

        private:
            virtual void shoot() override;
            unique<BulletShooter> m_shooter;
    };
}