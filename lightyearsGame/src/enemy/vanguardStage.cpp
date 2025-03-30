#include "enemy/vanguardStage.hpp"
#include "enemy/vanguard.hpp"
#include <framework/world.hpp>

ly::VanguardStage::VanguardStage(World *world)
    : GameStage{world},
      m_spawnInterval{1.5f},
      m_switchInterval{5.f},
      m_spawnDistanceToEdge{100.f},
      m_leftSpawnLocation{0.f, 0.f},
      m_rightSpawnLocation{0.f, 0.f},
      m_spawnLocation{0.f, 0.f},
      m_rowsToSpawn{2},
      m_rowSpawnCount{0},
      m_vanguardsPerRow{5},
      m_vanguardSpawnCount{0}
{
}

void ly::VanguardStage::startStage()
{
    auto windowSize = getWorld()->getWindowSize();
    m_leftSpawnLocation = sf::Vector2f{m_spawnDistanceToEdge, -100};
    m_rightSpawnLocation = sf::Vector2f{windowSize.x - m_spawnDistanceToEdge, -100};

    switchRow();
}

void ly::VanguardStage::switchRow()
{
    if (m_rowSpawnCount == m_rowsToSpawn)
    {
        finishStage();
        return;
    }

    if (m_spawnLocation == m_leftSpawnLocation)
    {
        m_spawnLocation = m_rightSpawnLocation;
    }
    else
    {
        m_spawnLocation = m_leftSpawnLocation;
    }

    m_spawnTimerHandle = TimerManager::get().setTimer(getWeakRef(), &VanguardStage::spawnVanguard, m_spawnInterval, true);

    m_rowSpawnCount++;
}

void ly::VanguardStage::spawnVanguard()
{
    weak<Vanguard> newVanguard = getWorld()->spawnAcotr<Vanguard>();
    newVanguard.lock()->setActorLocation(m_spawnLocation);
    m_vanguardSpawnCount++;
    if (m_vanguardSpawnCount == m_vanguardsPerRow)
    {
        TimerManager::get().clearTimer(m_spawnTimerHandle);
        m_switchTimerHandle = TimerManager::get().setTimer(getWeakRef(), &VanguardStage::switchRow, m_switchInterval, false);
        m_vanguardSpawnCount = 0;
    }
}

void ly::VanguardStage::stageFinished()
{
    TimerManager::get().clearTimer(m_switchTimerHandle);
    TimerManager::get().clearTimer(m_spawnTimerHandle);
}