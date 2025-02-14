#include "weapon/FrontalWiper.hpp"

ly::FrontalWiper::FrontalWiper(Actor *owner, float coolDownTime, const sf::Vector2f &localOffset, float width)
    : Shooter{owner},
      m_width{width},
      m_shooter1{owner, coolDownTime, {localOffset.x, localOffset.y - m_width / 2.f}, 0.f, "PNG/lasers/laserGreen11.png"},
      m_shooter2{owner, coolDownTime, {localOffset.x, localOffset.y - m_width / 6.f}, 0.f, "PNG/lasers/laserBlue07.png"},
      m_shooter3{owner, coolDownTime, {localOffset.x, localOffset.y + m_width / 6.f}, 0.f, "PNG/lasers/laserBlue07.png"},
      m_shooter4{owner, coolDownTime, {localOffset.x, localOffset.y + m_width / 2.f}, 0.f, "PNG/lasers/laserGreen11.png"},
      m_shooter5{owner, coolDownTime, {localOffset.x, localOffset.y + m_width / 1.f}, 0.f, "PNG/lasers/laserGreen11.png"},
      m_shooter6{owner, coolDownTime, {localOffset.x, localOffset.y - m_width / 1.f}, 0.f, "PNG/lasers/laserGreen11.png"}
{
}

void ly::FrontalWiper::increaseLevel(int amt)
{
    Shooter::increaseLevel(amt);
    m_shooter1.increaseLevel(amt);
    m_shooter2.increaseLevel(amt);
    m_shooter3.increaseLevel(amt);
    m_shooter4.increaseLevel(amt);
    m_shooter5.increaseLevel(amt);
    m_shooter6.increaseLevel(amt);
}

void ly::FrontalWiper::shootImp()
{
    m_shooter1.shoot();
    m_shooter2.shoot();
    m_shooter3.shoot();
    m_shooter4.shoot();

    if (isMaxLevel())
    {
        m_shooter5.shoot();
        m_shooter6.shoot();
    }
}
