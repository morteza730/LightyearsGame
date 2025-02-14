#include "weapon/shooter.hpp"
#include "framework/actor.hpp"

ly::Shooter::Shooter(Actor *owner) :
    m_owner{owner},
    m_currentLevel{1},
    m_maxLevel{4}
{
}

void ly::Shooter::increaseLevel(int amt)
{
    if (isMaxLevel())
        return;

    m_currentLevel++;
}

void ly::Shooter::shoot(){
    if (canShoot() && !isOnCoolDown()){
        shootImp();
    }
}