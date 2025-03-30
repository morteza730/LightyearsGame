#include "enemy/ufo.hpp"

ly::UFO::UFO(World *world, const sf::Vector2f &velocity, const std::string &texture_path, float rotationVelocity)
    : EnemySpaceship{world, texture_path},
      m_rotationVelocity{rotationVelocity},
      m_shooter1{new BulletShooter{this, 0.5f, {0.f, 0.f}, 0}},
      m_shooter2{new BulletShooter{this, 0.5f, {0.f, 0.f}, 120}},
      m_shooter3{new BulletShooter{this, 0.5f, {0.f, 0.f}, 240}}
{
    setVelocity(velocity);
}

void ly::UFO::tick(float deltaTime)
{
    EnemySpaceship::tick(deltaTime);
    shoot();
    addActorRotationOffset(m_rotationVelocity * deltaTime);
}

void ly::UFO::shoot()
{
    m_shooter1->shoot();
    m_shooter2->shoot();
    m_shooter3->shoot();
}
