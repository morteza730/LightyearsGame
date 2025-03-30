#include "enemy/chaosStage.hpp"
#include <framework/world.hpp>
#include <framework/mathutility.hpp>
#include "enemy/vanguard.hpp"
#include "enemy/twinBlade.hpp"
#include "enemy/ufo.hpp"
#include "enemy/hexagon.hpp"

ly::ChaosStage::ChaosStage(World *world)
    : GameStage{world},
      m_spawnInterval{4.f},
      m_minSpawnInterval{0.8f},
      m_spawnIntervalDecrement{0.5f},
      m_spawnIntervalDecrementInterval{5.f},
      m_stageDuration{60.f}
{
}

void ly::ChaosStage::startStage()
{
    m_spawnTimer = TimerManager::get().setTimer(getWeakRef(), &ChaosStage::spawnVanguard, m_spawnInterval);
    m_dificultyTimer = TimerManager::get().setTimer(getWeakRef(), &ChaosStage::increaseDifficulty, m_spawnIntervalDecrementInterval, true);
    TimerManager::get().setTimer(getWeakRef(), &ChaosStage::stageDurationReached, m_stageDuration);
}

void ly::ChaosStage::stageFinished()
{
    TimerManager::get().clearTimer(m_dificultyTimer);
    TimerManager::get().clearTimer(m_spawnTimer);
}

void ly::ChaosStage::spawnVanguard()
{
    weak<Vanguard> newVanguard = getWorld()->spawnAcotr<Vanguard>();
    newVanguard.lock()->setActorLocation(getRandomeSpawnLocationTop());
    m_spawnTimer = TimerManager::get().setTimer(getWeakRef(), &ChaosStage::spawnTwinBlade, m_spawnInterval);
}

void ly::ChaosStage::spawnTwinBlade()
{
    weak<TwinBlade> newTwinBlade = getWorld()->spawnAcotr<TwinBlade>();
    newTwinBlade.lock()->setActorLocation(getRandomeSpawnLocationTop());
    m_spawnTimer = TimerManager::get().setTimer(getWeakRef(), &ChaosStage::spawnHexegon, m_spawnInterval);
}

void ly::ChaosStage::spawnHexegon()
{
    weak<Hexagon> newHexegon = getWorld()->spawnAcotr<Hexagon>();
    newHexegon.lock()->setActorLocation(getRandomeSpawnLocationTop());
    m_spawnTimer = TimerManager::get().setTimer(getWeakRef(), &ChaosStage::spawnUFO, m_spawnInterval);
}

void ly::ChaosStage::spawnUFO()
{
    sf::Vector2f spawnLocation{getRandomeSpawnLocationSide()};
    sf::Vector2u windowSize = getWorld()->getWindowSize();
    sf::Vector2f windowCenter{windowSize.x / 2.f, windowSize.y / 2.f};
    sf::Vector2f velocityDirection = windowCenter - spawnLocation;
    normalize(velocityDirection);
    sf::Vector2f velocity{200.f * velocityDirection};

    weak<UFO> newUFO = getWorld()->spawnAcotr<UFO>(velocity);
    newUFO.lock()->setActorLocation(spawnLocation);

    m_spawnTimer = TimerManager::get().setTimer(getWeakRef(), &ChaosStage::spawnVanguard, m_spawnInterval);
}

void ly::ChaosStage::increaseDifficulty()
{
    if (m_spawnInterval > m_minSpawnInterval)
    {
        m_spawnInterval -= m_spawnIntervalDecrement;
    }
}

void ly::ChaosStage::stageDurationReached()
{
    finishStage();
}

sf::Vector2f ly::ChaosStage::getRandomeSpawnLocationTop()
{
    auto windowSize = getWorld()->getWindowSize();
    float spawnX = randomRange(100.f, windowSize.x - 100.f);
    float spawnY = -100.f;
    return {spawnX, spawnY};
}

sf::Vector2f ly::ChaosStage::getRandomeSpawnLocationSide()
{
    float spawnLocationX;
    float spawnLocationY;
    sf::Vector2u windowSize = getWorld()->getWindowSize();
    float rand = randomRange(-1.f, 1.f);
    if (rand > 0)
    {
        spawnLocationX = -100.f;
    }
    else
    {
        spawnLocationX = windowSize.x + 100.f;
    }
    spawnLocationY = randomRange(0, windowSize.y);
    return sf::Vector2f{spawnLocationX, spawnLocationY};
}
