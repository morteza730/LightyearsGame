#include "weapon/bulletshooter.hpp"
#include <framework/core.hpp>
// #include <framework/actor.hpp>
#include <framework/world.hpp>
#include "weapon/bullet.hpp"

ly::BulletShooter::BulletShooter(Actor* owner,float coolDownTime):
Shooter{owner},
m_coolDownTime{coolDownTime}
{}

bool ly::BulletShooter::isOnCoolDown() const 
{
    if (m_coolDownTimer.getElapsedTime().asSeconds() > m_coolDownTime){
        return false;
    }
    return true;
}

void ly::BulletShooter::shootImp()
{
    m_coolDownTimer.restart();
    weak<Bullet> bullet = getOwner()->getWorld()->spawnAcotr<Bullet>(getOwner(),"PNG/Lasers/laserBlue01.png");
    bullet.lock()->setActorLocation(getOwner()->getActorLocation());
    bullet.lock()->setActorRotation(getOwner()->getActorRotaion());
}
