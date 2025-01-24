#pragma once

#include "Spaceship/Spaceship.hpp"

namespace ly
{
    class EnemySpaceship : public Spaceship
    {
        public:
            EnemySpaceship(World *world,const std::string &texture_path="",float collisionDamage=200.f);
            virtual void tick(float deltaTime) override;

        private:
            float m_collisionDamage;
            virtual void onActorBeginOverlap(Actor *other) override;

    };

}