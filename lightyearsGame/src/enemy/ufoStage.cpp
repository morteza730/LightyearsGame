#include "enemy/ufoStage.hpp"
#include "enemy/ufo.hpp"
#include <framework/world.hpp>
#include <framework/mathutility.hpp>

ly::UFOStage::UFOStage(World *world)
    : GameStage{world},
      m_spawnInterval{4.f},
      m_spawnAmt{5},
      m_spawnCount{0},
      m_UFOSpeed{200.f}
{
}

void ly::UFOStage::startStage()
{
    m_spawnTimerHandle = TimerManager::get().setTimer(getWeakRef(), &UFOStage::spawnUFO, m_spawnInterval, true);
}

void ly::UFOStage::stageFinished()
{
    TimerManager::get().clearTimer(m_spawnTimerHandle);
}

void ly::UFOStage::spawnUFO()
{
    sf::Vector2f spawnLocation{getRandomLocation()};
    sf::Vector2u windowSize = getWorld()->getWindowSize();
    sf::Vector2f windowCenter{windowSize.x / 2.f, windowSize.y / 2.f};
    sf::Vector2f velocityDirection = windowCenter - spawnLocation;
    normalize(velocityDirection);
    sf::Vector2f velocity{m_UFOSpeed * velocityDirection};

    weak<UFO> newUFO = getWorld()->spawnAcotr<UFO>(velocity);
    newUFO.lock()->setActorLocation(spawnLocation);

    if (++m_spawnCount == m_spawnAmt)
    {
        finishStage();
    }
}

sf::Vector2f ly::UFOStage::getRandomLocation() const
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