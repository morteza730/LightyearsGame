#include "vfx/particle.hpp"
#include "framework/mathutility.hpp"

ly::Particle::Particle(World *world, const std::string &texture_path) : Actor(world, texture_path),
                                                                        m_velocity{},
                                                                        m_lifeTime{1.f},
                                                                        m_timer{}
{
}

void ly::Particle::tick(float deltaTime)
{
    if (m_timer.getElapsedTime().asSeconds() > m_lifeTime)
    {
        destroy();
    }

    Actor::tick(deltaTime);

    move(deltaTime);
    fade(deltaTime);
}

void ly::Particle::setRandomVelocity(float minSpeed, float maxSpeed)
{
    m_velocity = randomUnitVector() * randomRange(minSpeed, maxSpeed);
}

void ly::Particle::setRandomSize(float min, float max)
{
    float random = randomRange(min,max);
    getSprite().setScale(random,random);
}

void ly::Particle::setRandomLifeTime(float min, float max)
{
    m_lifeTime = randomRange(min,max);
}

void ly::Particle::move(float deltaTime)
{
    addActorLocationOffset(m_velocity * deltaTime);
}

void ly::Particle::fade(float deltaTime)
{
    float elapsedTime = m_timer.getElapsedTime().asSeconds();

    sf::Color fadingColor = lerpColor(getSprite().getColor(), sf::Color(255, 255, 255, 0), elapsedTime / m_lifeTime);
    getSprite().setColor(fadingColor);

    sf::Vector2f fadingScale = lerpVector(getSprite().getScale(), sf::Vector2f{}, elapsedTime / m_lifeTime);
    getSprite().setScale(fadingScale);
}
