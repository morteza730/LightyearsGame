#include <framework/mathutility.hpp>
#include <framework/world.hpp>
#include <vfx/particle.hpp>
#include "vfx/explosion.hpp"

ly::Explosion::Explosion(int particleAmount, float lifeTimeMin, float lifeTimeMax, float sizeMin, float sizeMax, float speedMin, float m_speedMax,const sf::Color& particleColor, List<std::string> particleImagePathes)
    :m_particleAmountt{particleAmount},
    m_lifeTimeMin{lifeTimeMin},
    m_lifeTimeMax{lifeTimeMax},
    m_sizeMin{sizeMin},
    m_sizeMax{sizeMax},
    m_speedMin{speedMin},
    m_speedMax{m_speedMax},
    m_particleColor{particleColor},
    m_particleImagePathes{particleImagePathes}
{
}

void ly::Explosion::spawnExplosion(World *world, const sf::Vector2f &location)
{
    if (!world)
    {
        return;
    }

    for (int i = 0; i < m_particleAmountt; i++)
    {
        int randomImageIndex = (int)randomRange(0, m_particleImagePathes.size());
        std::string particleImagePath = m_particleImagePathes.at(randomImageIndex);
        weak<Particle> newParticle = world->spawnAcotr<Particle>(particleImagePath);

        newParticle.lock()->setRandomLifeTime(m_lifeTimeMin, m_lifeTimeMax);
        newParticle.lock()->setRandomVelocity(m_speedMin, m_speedMax);
        newParticle.lock()->setRandomSize(m_sizeMin, m_sizeMax);
        newParticle.lock()->setActorLocation(location);
        newParticle.lock()->getSprite().setColor(m_particleColor);
    }
}