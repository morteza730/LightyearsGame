#pragma once

#include <framework/actor.hpp>

namespace ly{
    class SpaceShip:public Actor{
        public:
            SpaceShip(World *world,const std::string &texture_path="");
            virtual void tick(float deltaTime);
            void setVelocity(const sf::Vector2f& new_velocity);
            sf::Vector2f getVelocity() const {return m_velocity;}
        private:
            sf::Vector2f m_velocity;
    };
}