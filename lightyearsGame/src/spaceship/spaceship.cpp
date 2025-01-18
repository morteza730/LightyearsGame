#include <framework/mathutility.hpp>
#include "spaceship/spaceship.hpp"
#include "vfx/explosion.hpp"

ly::SpaceShip::SpaceShip(World *world, const std::string &texture_path) : Actor(world, texture_path),
                                                                          m_healthComponent{100.f, 100.f},
                                                                          m_blinkTime{0.f},
                                                                          m_blinkDuration{0.2f},
                                                                          m_blinkColorOffset{255, 0, 0, 255}
{
}

void ly::SpaceShip::tick(float deltaTime)
{
    Actor::tick(deltaTime);
    addActorLocationOffset(deltaTime * getVelocity());
    updateBlink(deltaTime);
}

void ly::SpaceShip::setVelocity(const sf::Vector2f &new_velocity)
{
    m_velocity = new_velocity;
}

void ly::SpaceShip::shoot()
{
}

void ly::SpaceShip::beginPlay()
{
    Actor::beginPlay();
    setEnablePhysics(true);

    m_healthComponent.onHealthChanged.bindAction(getWeakRef(), &SpaceShip::onHealthChanged);
    m_healthComponent.onTakenDamage.bindAction(getWeakRef(), &SpaceShip::onTakenDamage);
    m_healthComponent.onHealthEmpty.bindAction(getWeakRef(), &SpaceShip::blow);
}

void ly::SpaceShip::applyDamage(float amt)
{
    m_healthComponent.changeHealth(-amt);
}

void ly::SpaceShip::onHealthChanged(float amt, float health, float maxHealth)
{
}

void ly::SpaceShip::blink()
{
    if (m_blinkTime == 0)
    {
        m_blinkTime = m_blinkDuration;
    }
}

void ly::SpaceShip::updateBlink(float deltaTime)
{
    if (m_blinkTime <= 0)
        return;

    m_blinkTime -= deltaTime;
    m_blinkTime = (m_blinkTime > 0) ? m_blinkTime : 0.f;

    sf::Color blinkColor = lerpColor(sf::Color::White,m_blinkColorOffset,m_blinkTime);
    getSprite().setColor(blinkColor);
}

void ly::SpaceShip::onTakenDamage(float amt, float health, float maxHealth)
{
    blink();
}

void ly::SpaceShip::blow()
{
    Explosion *explosion = new Explosion();
    explosion->spawnExplosion(getWorld(), getActorLocation());
    distroy();
    delete explosion;
}
