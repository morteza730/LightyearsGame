#include "enemy/hexagon.hpp"

ly::Hexagon::Hexagon(World *world, const std::string &texture_path, const sf::Vector2f &velocity)
    :EnemySpaceship{world,texture_path},
    m_shooter1{new BulletShooter{this,1.f,{20.f,50.f},30}},
    m_shooter2{new BulletShooter{this,1.f,{20.f,-50.f},-30}},
    m_shooter3{new BulletShooter{this,1.f,{50.f,0.f},0}},
    m_shooter4{new BulletShooter{this,1.f,{-50.f,0.f},-180}},
    m_shooter5{new BulletShooter{this,1.f,{-20.f,50.f},120}},
    m_shooter6{new BulletShooter{this,1.f,{-20.f,-50.f},-120}}
{
    setVelocity(velocity);
}

void ly::Hexagon::tick(float deltaTime)
{
    EnemySpaceship::tick(deltaTime);
    shoot();
}

void ly::Hexagon::shoot()
{
    m_shooter1->shoot();
    m_shooter2->shoot();
    m_shooter3->shoot();
    m_shooter4->shoot();
    m_shooter5->shoot();
    m_shooter6->shoot();
}
