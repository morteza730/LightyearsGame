#include "spaceship/spaceship.hpp"

ly::SpaceShip::SpaceShip(World *world, const std::string &texture_path):
Actor(world, texture_path)
{
}

void ly::SpaceShip::tick(float deltaTime)
{
    Actor::tick(deltaTime);
    addActorLocationOffset(deltaTime*getVelocity());
}
void ly::SpaceShip::setVelocity(const sf::Vector2f &new_velocity)
{
    m_velocity = new_velocity;
}