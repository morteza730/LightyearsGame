#include "player/reward.hpp"
#include "player/playerspaceship.hpp"
#include "weapon/threeWayShooter.hpp"
#include "weapon/FrontalWiper.hpp"
#include <framework/world.hpp>

ly::Reward::Reward(World *world, const std::string &texture_path, RewardFunc rewardFunc, float speed)
    : Actor{world, texture_path},
    m_rewardFunc{rewardFunc},
    m_speed{speed}
{
}

void ly::Reward::beginPlay()
{
    Actor::beginPlay();
    setEnablePhysics(true);
}

void ly::Reward::tick(float deltaTime)
{
    Actor::tick(deltaTime);
    addActorLocationOffset({0.f, deltaTime * m_speed});
}

void ly::Reward::onActorBeginOverlap(Actor *other)
{
    PlayerSpaceship *playerSpaceship = dynamic_cast<PlayerSpaceship *>(other);

    if (playerSpaceship == nullptr || playerSpaceship->isPendingDistroyed())
        return;

    m_rewardFunc(playerSpaceship);
    destroy();
}

ly::weak<ly::Reward> ly::createHealthReward(World *world)
{
    return createReward(world,"PNG/Power-ups/pill_green.png",rewardHealth);
}

ly::weak<ly::Reward> ly::createThreeWayShooterReward(World *world)
{
    return createReward(world,"PNG/Power-ups/bolt_gold.png",rewardThreeWayShooter);
}

ly::weak<ly::Reward> ly::createFrontalWiperReward(World *world)
{
    return createReward(world,"PNG/Power-ups/shield_gold.png",rewardFrontalWiper);
}

ly::weak<ly::Reward> ly::createReward(World *world, const std::string &texturePath, RewardFunc rewardFunc)
{
    weak<Reward> reward = world->spawnAcotr<Reward>(texturePath,rewardFunc);
    return reward;
}

void ly::rewardHealth(PlayerSpaceship *player)
{
    static float rewardAmt = 10.f;

    if (!player || player->isPendingDistroyed())
        return;

    player->getHealthComponent().changeHealth(rewardAmt);
}

void ly::rewardThreeWayShooter(PlayerSpaceship *player)
{
    if (!player || player->isPendingDistroyed())
        return;

    player->setShooter(unique<Shooter>{new ThreeWayShooter{player, 0.4, {50.f, 0.f}}});
}

void ly::rewardFrontalWiper(PlayerSpaceship *player)
{
    if (!player || player->isPendingDistroyed())
        return;

    player->setShooter(unique<Shooter>{new FrontalWiper{player, 0.4, {50.f, 0.f}}});
}
