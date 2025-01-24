#include "weapon/bullet.hpp"

ly::Bullet::Bullet(World *world, Actor *owner, const std::string &texture_path, float damage, float speed) : Actor{world, texture_path},
                                                                                                             m_owner{owner},
                                                                                                             m_damage{damage},
                                                                                                             m_speed{speed}
{
    setTeamID(owner->getTeamID());
}

void ly::Bullet::setSpeed(float newSpeed)
{
    m_speed = newSpeed;
}

void ly::Bullet::setDamage(float newdamage)
{
    m_damage = newdamage;
}

void ly::Bullet::tick(float deltaTime)
{
    Actor::tick(deltaTime);
    move(deltaTime);
    if (isActorOutOfWindowsBounds())
    {
        destroy();
    }
}

void ly::Bullet::beginPlay()
{
    Actor::beginPlay();
    setEnablePhysics(true);
}

void ly::Bullet::move(float deltaTime)
{
    addActorLocationOffset(getActorForwardDirection() * m_speed * deltaTime);
}

void ly::Bullet::onActorBeginOverlap(Actor *other)
{
    if (isOtherHostile(other))
    {
        other->applyDamage(getDamage());
        destroy();
    }
}