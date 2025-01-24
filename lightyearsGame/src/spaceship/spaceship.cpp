#include <framework/mathutility.hpp>
#include "Spaceship/Spaceship.hpp"
#include "vfx/explosion.hpp"

ly::Spaceship::Spaceship(World *world, const std::string &texture_path) : Actor(world, texture_path),
                                                                          m_healthComponent{100.f, 100.f},
                                                                          m_blinkTime{0.f},
                                                                          m_blinkDuration{0.2f},
                                                                          m_blinkColorOffset{255, 0, 0, 255}
{
}

void ly::Spaceship::tick(float deltaTime)
{
    Actor::tick(deltaTime);
    addActorLocationOffset(deltaTime * getVelocity());
    updateBlink(deltaTime);
}

void ly::Spaceship::setVelocity(const sf::Vector2f &new_velocity)
{
    m_velocity = new_velocity;
}

void ly::Spaceship::shoot()
{
}

void ly::Spaceship::beginPlay()
{
    Actor::beginPlay();
    setEnablePhysics(true);

    m_healthComponent.onHealthChanged.bindAction(getWeakRef(), &Spaceship::onHealthChanged);
    m_healthComponent.onTakenDamage.bindAction(getWeakRef(), &Spaceship::onTakenDamage);
    m_healthComponent.onHealthEmpty.bindAction(getWeakRef(), &Spaceship::blow);
}

void ly::Spaceship::applyDamage(float amt)
{
    m_healthComponent.changeHealth(-amt);
}

void ly::Spaceship::onHealthChanged(float amt, float health, float maxHealth)
{
}

void ly::Spaceship::blink()
{
    if (m_blinkTime == 0)
    {
        m_blinkTime = m_blinkDuration;
    }
}

void ly::Spaceship::updateBlink(float deltaTime)
{
    if (m_blinkTime <= 0)
        return;

    m_blinkTime -= deltaTime;
    m_blinkTime = (m_blinkTime > 0) ? m_blinkTime : 0.f;

    sf::Color blinkColor = lerpColor(sf::Color::White,m_blinkColorOffset,m_blinkTime);
    getSprite().setColor(blinkColor);
}

void ly::Spaceship::onTakenDamage(float amt, float health, float maxHealth)
{
    blink();
}

void ly::Spaceship::blow()
{
    Explosion *explosion = new Explosion();
    explosion->spawnExplosion(getWorld(), getActorLocation());
    destroy();
    delete explosion;
}
