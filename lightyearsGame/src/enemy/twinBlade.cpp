#include "enemy/twinBlade.hpp"

ly::TwinBlade::TwinBlade(World *world, const std::string &texture_path, const sf::Vector2f &velocity)
    : EnemySpaceship{world, texture_path},
      m_shooterLeft{new BulletShooter{this, 1.f, {-50, 20},180}},
      m_shooterRight{new BulletShooter{this, 1.f, {-50, -20},180}}
{
    setVelocity(velocity);
}

void ly::TwinBlade::tick(float deltaTime)
{
    EnemySpaceship::tick(deltaTime);
    shoot();
}

void ly::TwinBlade::shoot()
{
    m_shooterLeft->shoot();
    m_shooterRight->shoot();
}
