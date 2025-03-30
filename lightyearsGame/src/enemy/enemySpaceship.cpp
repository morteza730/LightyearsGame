#include "enemy/enemySpaceship.hpp"
#include "player/playerManager.hpp"
#include <framework/mathutility.hpp>

ly::EnemySpaceship::EnemySpaceship(World *world, const std::string &texture_path, float collisionDamage, float rewardSpawnWeight, const List<RewardFactoryFunc> rewardFactories)
    : Spaceship{world, texture_path},
      m_collisionDamage{collisionDamage},
      m_rewardFactories{rewardFactories},
      m_scoreAwardAmt{10},
      m_rewardSpawnWeight{rewardSpawnWeight}
{
    setTeamID(2);
}

void ly::EnemySpaceship::tick(float deltaTime)
{
    Spaceship::tick(deltaTime);
    if (isActorOutOfWindowsBounds(getActorGlobalBounds().width * 2.f))
    {
        destroy();
    }
}

void ly::EnemySpaceship::setScoreAwardAmt(unsigned int amt)
{
    m_scoreAwardAmt = amt;
}

void ly::EnemySpaceship::setRewardSpawnWeight(float weight)
{
    if (weight < 0 || weight>1)
        return;

    m_rewardSpawnWeight = weight;
}

void ly::EnemySpaceship::spawnReward()
{
    if (m_rewardFactories.size() == 0)
        return;

    if (m_rewardSpawnWeight < randomRange(0,1))
        return;

    int pick = (int)randomRange(0, m_rewardFactories.size());

    if (pick < 0 || pick >= m_rewardFactories.size())
        return;

    weak<Reward> newReward = m_rewardFactories[pick](getWorld());
    newReward.lock()->setActorLocation(getActorLocation());
}

void ly::EnemySpaceship::onActorBeginOverlap(Actor *other)
{
    Spaceship::onActorBeginOverlap(other);

    if (!isOtherHostile(other))
        return;

    other->applyDamage(m_collisionDamage);
}

void ly::EnemySpaceship::blew()
{
    spawnReward();

    Player *player = PlayerManager::get().getPlayer();

    if (!player || player->isPendingDistroyed())
        return;

    player->addScore(m_scoreAwardAmt);
}