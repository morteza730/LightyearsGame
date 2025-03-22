#include "weapon/threeWayShooter.hpp"

ly::ThreeWayShooter::ThreeWayShooter(Actor *owner, float coolDownTime, const sf::Vector2f &localOffset, float rotationalOffset)
    : Shooter{owner},
      m_ShooterLeft{owner, coolDownTime, localOffset + sf::Vector2f{10.f, -10.f}, -30.f + rotationalOffset, "PNG/lasers/laserRed01.png"},
      m_ShooterMiddle{owner, coolDownTime, localOffset, 0.f + rotationalOffset, "PNG/lasers/laserRed01.png"},
      m_ShooterRight{owner, coolDownTime, localOffset + sf::Vector2f{10.f, 10.f}, 30.f + rotationalOffset, "PNG/lasers/laserRed01.png"},
      m_topLevelShooterLeft{owner, coolDownTime, localOffset + sf::Vector2f{10.f, -5.f}, -15.f + rotationalOffset, "PNG/lasers/laserRed01.png"},
      m_topLevelShooterRight{owner, coolDownTime, localOffset + sf::Vector2f{10.f, 5.f}, 15.f + rotationalOffset, "PNG/lasers/laserRed01.png"}
{
}

void ly::ThreeWayShooter::setCurrentLevel(int level)
{
    Shooter::setCurrentLevel(level);
    m_ShooterLeft.setCurrentLevel(level);
    m_ShooterMiddle.setCurrentLevel(level);
    m_ShooterRight.setCurrentLevel(level);
    m_topLevelShooterLeft.setCurrentLevel(level);
    m_topLevelShooterRight.setCurrentLevel(level);
}

void ly::ThreeWayShooter::increaseLevel(int amt)
{
    Shooter::increaseLevel(amt);
    m_ShooterLeft.increaseLevel(amt);
    m_ShooterMiddle.increaseLevel(amt);
    m_ShooterRight.increaseLevel(amt);
    m_topLevelShooterLeft.increaseLevel(amt);
    m_topLevelShooterRight.increaseLevel(amt);
}

void ly::ThreeWayShooter::shootImp()
{
    m_ShooterLeft.shoot();
    m_ShooterMiddle.shoot();
    m_ShooterRight.shoot();

    if (isMaxLevel())
    {
        m_topLevelShooterLeft.shoot();
        m_topLevelShooterRight.shoot();
    }
}