#pragma once

#include <framework/actor.hpp>
#include <functional>

namespace ly
{
    class PlayerSpaceship;
    class Reward;
    using RewardFunc = std::function<void(PlayerSpaceship *)>;
    using RewardFactoryFunc = std::function<weak<Reward>(World *)>;

    class Reward : public Actor
    {
    public:
        Reward(World *world, const std::string &texture_path, RewardFunc rewardFunc, float speed = 200);
        virtual void beginPlay() override;
        virtual void tick(float deltaTime) override;

    private:
        virtual void onActorBeginOverlap(Actor *other) override;
        float m_speed;
        RewardFunc m_rewardFunc;
    };

    weak<Reward> createHealthReward(World *world);
    weak<Reward> createThreeWayShooterReward(World *world);
    weak<Reward> createFrontalWiperReward(World *world);
    weak<Reward> createLifeReward(World *world);

    weak<Reward> createReward(World *world, const std::string &texturePath, RewardFunc rewardFunc);

    void rewardHealth(PlayerSpaceship *player);
    void rewardLife(PlayerSpaceship *player);
    void rewardThreeWayShooter(PlayerSpaceship *player);
    void rewardFrontalWiper(PlayerSpaceship *player);
}