#pragma once

#include "framework/actor.hpp"

namespace ly
{
    class Particle : public Actor
    {
    public:
        Particle(World *world, const std::string &texture_path);

        virtual void tick(float deltaTime) override;

        virtual void setRandomVelocity(float minSpeed, float maxSpeed);
        virtual void setRandomSize(float min, float max);
        virtual void setRandomLifeTime(float min, float max);

    protected:
        virtual void move(float deltaTime);
        virtual void fade(float deltaTime);

    private:
        sf::Vector2f m_velocity;
        float m_lifeTime;
        sf::Clock m_timer;
    };
}
