#include "gameplay/waitstage.hpp"
#include "framework/timermanager.hpp"


ly::WaitStage::WaitStage(World * world, float waitDuration)
    : GameStage{world},
    m_waitDuration{waitDuration}
{
}

void ly::WaitStage::startStage()
{
    TimerManager::get().setTimer(getWeakRef(),&WaitStage::finishStage,m_waitDuration,false);
}