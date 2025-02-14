#include "weapon/bulletshooter.hpp"
#include <framework/core.hpp>
#include <framework/world.hpp>
#include "weapon/bullet.hpp"

ly::BulletShooter::BulletShooter(Actor *owner, float coolDownTime, const sf::Vector2f &localPositionOffset, float localRotationOffset, const std::string &texturePath)
    : Shooter{owner},
      m_coolDownTime{coolDownTime},
      m_localPositionOffset{localPositionOffset},
      m_localRotationOffset{localRotationOffset},
      m_bulletTexturePath{texturePath}
{
}

bool ly::BulletShooter::isOnCoolDown() const
{
    if (m_coolDownTimer.getElapsedTime().asSeconds() > (m_coolDownTime / getCurrentLevel()))
    {
        return false;
    }
    return true;
}

void ly::BulletShooter::setBulletTexturePath(const std::string &texturePath)
{
    m_bulletTexturePath = texturePath;
}

void ly::BulletShooter::shootImp()
{
    sf::Vector2f ownerForwardDir = getOwner()->getActorForwardDirection();
    sf::Vector2f ownerRightDir = getOwner()->getActorRightDirection();

    m_coolDownTimer.restart();
    weak<Bullet> bullet = getOwner()->getWorld()->spawnAcotr<Bullet>(getOwner(), m_bulletTexturePath);
    bullet.lock()->setActorLocation(getOwner()->getActorLocation() + ownerForwardDir * m_localPositionOffset.x + ownerRightDir * m_localPositionOffset.y);
    bullet.lock()->setActorRotation(getOwner()->getActorRotaion() + m_localRotationOffset);
}
