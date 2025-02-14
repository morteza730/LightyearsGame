#pragma once

#include "Spaceship/Spaceship.hpp"
#include "player/reward.hpp"

namespace ly
{
    class EnemySpaceship : public Spaceship
    {
    public:
        EnemySpaceship(World *world,
                       const std::string &texture_path = "",
                       float collisionDamage = 200.f,
                       const List<RewardFactoryFunc> rewardFactories =
                           {
                               createHealthReward,
                               createThreeWayShooterReward,
                               createFrontalWiperReward});
        virtual void tick(float deltaTime) override;

    private:
        void spawnReward();
        float m_collisionDamage;
        virtual void onActorBeginOverlap(Actor *other) override;
        virtual void blew() override;
        List<RewardFactoryFunc> m_rewardFactories;
    };

}