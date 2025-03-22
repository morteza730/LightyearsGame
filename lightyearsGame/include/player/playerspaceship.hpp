#pragma once

#include "Spaceship/Spaceship.hpp"
#include <framework/timermanager.hpp>

namespace ly
{
    class Shooter;
    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World *world, const std::string &texture_path = "PNG/playerShip1_blue.png");
        ~PlayerSpaceship();
        virtual void tick(float deltaTime) override;
        virtual void shoot() override;
        virtual void beginPlay() override;
        virtual void applyDamage(float amt) override;
        float getSpeed() const { return m_speed; }
        void setSpeed(float new_speed) { m_speed = new_speed; }
        void setShooter(unique<Shooter> &&newShooter);

    private:
        void handleInput();
        void consumeInput();
        void normalizeInput(sf::Vector2f &vector);
        void clampInputOnEdge();
        void stopInvulnerable();
        void updateInvulnerable(float deltaTime);

        sf::Vector2f m_moveInput;
        float m_speed;
        unique<Shooter> m_shooter;

        float m_invulnerableTime;
        TimerHandle m_invulnerableTimer;
        bool m_invulnerable;

        float m_invulnerableFlashScaleMax;
        float m_invulnerableFlashScale;
        float m_invulnerableFlashDir;
    };
}