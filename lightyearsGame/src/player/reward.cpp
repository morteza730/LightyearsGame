#include "player/reward.hpp"
#include "player/playerManager.hpp"
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
    if (!other || other->isPendingDistroyed())
        return;

    Player *player = PlayerManager::get().getPlayer();

    if (!player || player->isPendingDistroyed())
        return;

    weak<PlayerSpaceship> playerSpaceship = player->getCurrentSpaceship();

    if (playerSpaceship.expired() || playerSpaceship.lock()->isPendingDistroyed())
        return;

    if (playerSpaceship.lock()->getUniqueID() == other->getUniqueID())
    {
        m_rewardFunc(playerSpaceship.lock().get());
        destroy();
    }
}

ly::weak<ly::Reward> ly::createHealthReward(World *world)
{
    return createReward(world, "PNG/Power-ups/pill_green.png", rewardHealth);
}

ly::weak<ly::Reward> ly::createLifeReward(World *world)
{
    return createReward(world, "PNG/UI/playerLife1_blue.png", rewardLife);
}

ly::weak<ly::Reward> ly::createThreeWayShooterReward(World *world)
{
    return createReward(world, "PNG/Power-ups/bolt_gold.png", rewardThreeWayShooter);
}

ly::weak<ly::Reward> ly::createFrontalWiperReward(World *world)
{
    return createReward(world, "PNG/Power-ups/shield_gold.png", rewardFrontalWiper);
}

ly::weak<ly::Reward> ly::createReward(World *world, const std::string &texturePath, RewardFunc rewardFunc)
{
    weak<Reward> reward = world->spawnAcotr<Reward>(texturePath, rewardFunc);
    return reward;
}

void ly::rewardHealth(PlayerSpaceship *player)
{
    static float rewardAmt = 10.f;

    if (!player || player->isPendingDistroyed())
        return;

    player->getHealthComponent().changeHealth(rewardAmt);
}

void ly::rewardLife(PlayerSpaceship *player)
{
    if (!PlayerManager::get().getPlayer())
        return;

    PlayerManager::get().getPlayer()->addLifeCount(1);
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
