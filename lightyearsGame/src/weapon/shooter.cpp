#include "weapon/shooter.hpp"
#include "framework/actor.hpp"

ly::Shooter::Shooter(Actor* owner):
    m_owner{owner}
{}

void ly::Shooter::shoot(){
    if (canShoot() && !isOnCoolDown()){
        shootImp();
    }
}