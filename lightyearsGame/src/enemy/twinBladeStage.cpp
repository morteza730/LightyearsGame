#include "enemy/twinBladeStage.hpp"
#include "enemy/twinBlade.hpp"
#include "framework/world.hpp"

ly::TwinBladeStage::TwinBladeStage(World *world)
    : GameStage{world},
      m_spawnInterval{1.5f},
      m_spawnDistanceToEdge{100.f},
      m_leftSpawnLocation{0.f, 0.f},
      m_rightSpawnLocation{0.f, 0.f},
      m_spawnLocation{0.f, 0.f},
      m_spawnAmt{10},
      m_spawnCount{0}
{
}

void ly::TwinBladeStage::startStage()
{
    auto windowSize = getWorld()->getWindowSize();
    m_leftSpawnLocation = sf::Vector2f{windowSize.x/2 + m_spawnDistanceToEdge, -100};
    m_rightSpawnLocation = sf::Vector2f{windowSize.x/2 - m_spawnDistanceToEdge, -100};
    m_spawnLocation = m_leftSpawnLocation;

    m_spawnTimerHandle = TimerManager::get().setTimer(getWeakRef(), &TwinBladeStage::spawnTwinBlade, m_spawnInterval, true);
}

void ly::TwinBladeStage::spawnTwinBlade()
{
    weak<TwinBlade> newTwinBlade = getWorld()->spawnAcotr<TwinBlade>();
    newTwinBlade.lock()->setActorLocation(m_spawnLocation);

    if (m_spawnLocation == m_leftSpawnLocation)
    {
        m_spawnLocation = m_rightSpawnLocation;
    }
    else
    {
        m_spawnLocation = m_leftSpawnLocation;
    }

    m_spawnCount++;

    if (m_spawnCount == m_spawnAmt)
        finishStage();
}

void ly::TwinBladeStage::stageFinished()
{
    TimerManager::get().clearTimer(m_spawnTimerHandle);
}
