#include "enemy/enemySpaceship.hpp"


ly::EnemySpaceship::EnemySpaceship(World *world, const std::string &texture_path, float collisionDamage):
    Spaceship(world,texture_path),
    m_collisionDamage(collisionDamage)
{
    setTeamID(2);
}

void ly::EnemySpaceship::tick(float deltaTime)
{
    Spaceship::tick(deltaTime);
    if (isActorOutOfWindowsBounds(getActorGlobalBounds().width))
    {
        destroy();
    }
}

void ly::EnemySpaceship::onActorBeginOverlap(Actor *other)
{
    Spaceship::onActorBeginOverlap(other);

    if (!isOtherHostile(other))
        return;

    other->applyDamage(m_collisionDamage);
}