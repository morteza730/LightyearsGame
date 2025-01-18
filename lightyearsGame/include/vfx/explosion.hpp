#pragma once

#include <string>
#include "framework/core.hpp"

namespace ly
{
    class World;
    class Explosion
    {
        public:
            Explosion(int particleAmount = 20,
            float lifeTimeMin = 0.5f,
            float lifeTimeMax = 2.f,
            float sizeMin = 1,
            float sizeMax = 3,
            float speedMin = 200,
            float m_speedMax = 400,
            const sf::Color& particleColor = sf::Color{255, 128,0, 255},
            List<std::string> particleImagePathes = {
                "PNG/Effects/star1.png",
                "PNG/Effects/star2.png",
                "PNG/Effects/star3.png"
            });

            void spawnExplosion(World *world, const sf::Vector2f& location);

        private:
            int m_particleAmountt;
            float m_lifeTimeMin;
            float m_lifeTimeMax;
            float m_sizeMin;
            float m_sizeMax;
            float m_speedMin;
            float m_speedMax;
            sf::Color m_particleColor;
            List<std::string> m_particleImagePathes;
    };
}