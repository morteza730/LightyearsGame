#pragma once

#include "spaceship/spaceship.hpp"

namespace ly{
    class BulletShooter;
    class PlayerSpaceShip:public SpaceShip
    {
        public:
            PlayerSpaceShip(World *world,const std::string &texture_path="PNG/playerShip1_blue.png");
            ~PlayerSpaceShip();
            virtual void tick(float deltaTime) override;
            float getSpeed() const {return m_speed;}
            void setSpeed(float new_speed){m_speed = new_speed;}
            virtual void shoot() override;

        private:
            void handleInput();
            void consumeInput();
            void normalizeInput(sf::Vector2f& vector);
            void clampInputOnEdge();
            sf::Vector2f m_moveInput;
            float m_speed;
            unique<BulletShooter> m_shooter;
    };
}