#pragma once

#include "enemy/enemySpaceship.hpp"
#include "weapon/bulletshooter.hpp"
#include "weapon/threeWayShooter.hpp"
#include "weapon/FrontalWiper.hpp"

namespace ly
{
    class Boss : public EnemySpaceship
    {
    public:
        Boss(World *world);
        virtual void tick(float deltaTime) override;
        virtual void beginPlay() override;

    private:
        void checkMove();
        float m_speed;
        float m_baseSpeed;
        float m_switchDistanceToEdge;
        void shootBaseShooters();
        void shootThreeWayShooter();
        void shootFrontalWiper();
        void shootFinalShooter();
        void healthChanged(float amt, float currentHealth, float maxHealth);
        void setStage(int newStage);
        BulletShooter m_baseShooterLeft;
        BulletShooter m_baseShooterRight;
        ThreeWayShooter m_threewayShooter;
        FrontalWiper m_frontalWiperRight;
        FrontalWiper m_frontalWiperLeft;
        BulletShooter m_finalShooterLeft;
        BulletShooter m_finalShooterRight;
        int m_stage;
    };
}