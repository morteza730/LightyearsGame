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
                       float rewardSpawnWeight = 0.5f,
                       const List<RewardFactoryFunc> rewardFactories =
                           {
                               createHealthReward,
                               createLifeReward,
                               createThreeWayShooterReward,
                               createFrontalWiperReward});
        virtual void tick(float deltaTime) override;
        void setScoreAwardAmt(unsigned int amt);
        void setRewardSpawnWeight(float weight);

    private:
        void spawnReward();
        virtual void onActorBeginOverlap(Actor *other) override;
        virtual void blew() override;
        float m_collisionDamage;
        List<RewardFactoryFunc> m_rewardFactories;
        unsigned int m_scoreAwardAmt;
        float m_rewardSpawnWeight;
    };

}