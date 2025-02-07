#include "gameplay/gamestage.hpp"
#include "framework/core.hpp"

ly::GameStage::GameStage(World *world)
    : m_world{world},
    m_stageFinished{false}
{
}

void ly::GameStage::startStage()
{
    LOG("start stage");
}

void ly::GameStage::tickStage(float deltaTime)
{
    // LOG("tick stage");
}

void ly::GameStage::finishStage()
{
    m_stageFinished = true;
    stageFinished();
    onStageFinished.broadCast();
}

void ly::GameStage::stageFinished()
{
    LOG("stage finished");
}
