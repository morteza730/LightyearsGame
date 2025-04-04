#pragma once

#include <framework/actor.hpp>
#include "gameplay/healthComponent.hpp"

namespace ly{

    class Spaceship:public Actor{
        public:
            Spaceship(World *world,const std::string &texture_path="");
            virtual void tick(float deltaTime);
            void setVelocity(const sf::Vector2f& new_velocity);
            sf::Vector2f getVelocity() const {return m_velocity;}
            virtual void shoot();
            virtual void beginPlay() override;
            virtual void applyDamage(float amt) override;
            HealthComponent &getHealthComponent() {return m_healthComponent;}
        private:
            void blink();
            void updateBlink(float deltaTime);
            virtual void onHealthChanged(float amt,float health,float maxHealth);
            virtual void onTakenDamage(float amt,float health,float maxHealth);
            void blow();
            virtual void blew();
            HealthComponent m_healthComponent;
            sf::Vector2f m_velocity;

            float m_blinkTime;
            float m_blinkDuration;
            sf::Color m_blinkColorOffset;
    };
}