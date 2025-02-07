#include "enemy/vanguard.hpp"

ly::Vanguard::Vanguard(World *world, const std::string &texture_path, const sf::Vector2f &velocity):
    EnemySpaceship(world,texture_path),
    m_shooter{new BulletShooter{this,1.f,{-50.f,0.f},180}}
{
    setVelocity(velocity);
    // setActorRotation(-180.f);
}

void ly::Vanguard::tick(float deltaTime)
{
    EnemySpaceship::tick(deltaTime);
    shoot();
}

void ly::Vanguard::shoot()
{
    m_shooter->shoot();
}