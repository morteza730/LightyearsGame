#pragma once

#include "enemy/enemySpaceship.hpp"
#include "weapon/bulletshooter.hpp"

namespace ly
{
    class Hexagon: public EnemySpaceship
    {
        public:
            Hexagon(World *world,const std::string &texture_path="PNG/Enemies/enemyBlack4.png",const sf::Vector2f &velocity = {0.f,100.f});
            virtual void tick(float deltaTime) override;

         private:
            virtual void shoot() override;
            unique<BulletShooter> m_shooter1;
            unique<BulletShooter> m_shooter2;
            unique<BulletShooter> m_shooter3;
            unique<BulletShooter> m_shooter4;
            unique<BulletShooter> m_shooter5;
            unique<BulletShooter> m_shooter6;
    };
}