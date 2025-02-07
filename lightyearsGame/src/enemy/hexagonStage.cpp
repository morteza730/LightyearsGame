#include "enemy/hexagonStage.hpp"
#include "enemy/hexagon.hpp"
#include <framework/world.hpp>

ly::HexagonStage::HexagonStage(World *world)
    : GameStage{world},
      m_spawnInterval{5.f},
      m_spawnSideDistance{80.f},
      m_spawnGroundAmt{5},
      m_spawnGroundCount{0},
      m_middleSpawnLocation{world->getWindowSize().x / 2.f, -100.f},
      m_rightSpawnLocation{world->getWindowSize().x / 2.f + m_spawnSideDistance, -100.f - m_spawnSideDistance},
      m_leftSpawnLocation{world->getWindowSize().x / 2.f - m_spawnSideDistance, -100.f - m_spawnSideDistance}
{
}

void ly::HexagonStage::startStage()
{
    m_spawnTimerHandle = TimerManager::get().setTimer(getWeakRef(), &HexagonStage::spawnHexagon, m_spawnInterval, true);
}

void ly::HexagonStage::spawnHexagon()
{
    weak<Hexagon> newHexagon = getWorld()->spawnAcotr<Hexagon>();
    newHexagon.lock()->setActorLocation(m_middleSpawnLocation);

    newHexagon = getWorld()->spawnAcotr<Hexagon>();
    newHexagon.lock()->setActorLocation(m_rightSpawnLocation);

    newHexagon = getWorld()->spawnAcotr<Hexagon>();
    newHexagon.lock()->setActorLocation(m_leftSpawnLocation);

    if (++m_spawnGroundCount == m_spawnGroundAmt)
        finishStage();
}

void ly::HexagonStage::stageFinished()
{
    TimerManager::get().clearTimer(m_spawnTimerHandle);
}