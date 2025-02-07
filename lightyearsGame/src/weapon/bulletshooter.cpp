#include "weapon/bulletshooter.hpp"
#include <framework/core.hpp>
#include <framework/world.hpp>
#include "weapon/bullet.hpp"

ly::BulletShooter::BulletShooter(Actor *owner, float coolDownTime, const sf::Vector2f &localPositionOffset, float localRotationOffset)
    : Shooter{owner},
      m_coolDownTime{coolDownTime},
      m_localPositionOffset{localPositionOffset},
      m_localRotationOffset{localRotationOffset}
{
}

bool ly::BulletShooter::isOnCoolDown() const
{
    if (m_coolDownTimer.getElapsedTime().asSeconds() > m_coolDownTime)
    {
        return false;
    }
    return true;
}

void ly::BulletShooter::shootImp()
{
    sf::Vector2f ownerForwardDir = getOwner()->getActorForwardDirection();
    sf::Vector2f ownerRightDir = getOwner()->getActorRightDirection();

    m_coolDownTimer.restart();
    weak<Bullet> bullet = getOwner()->getWorld()->spawnAcotr<Bullet>(getOwner(), "PNG/Lasers/laserBlue01.png");
    bullet.lock()->setActorLocation(getOwner()->getActorLocation() + ownerForwardDir * m_localPositionOffset.x + ownerRightDir * m_localPositionOffset.y);
    bullet.lock()->setActorRotation(getOwner()->getActorRotaion() + m_localRotationOffset);
}
