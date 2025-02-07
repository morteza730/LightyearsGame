#include "framework/world.hpp"
#include "framework/core.hpp"
#include "framework/actor.hpp"
#include "framework/application.hpp"
#include "gameplay/gamestage.hpp"

ly::World::World(Application *application)
    : m_beginPlay{false},
      owningApp{application},
      m_actors{},
      m_pendingActors{},
      m_gameStages{},
      m_currentStage{m_gameStages.end()}
{
}

ly::World::~World()
{
}

void ly::World::beginPlayInternal()
{
    if (!m_beginPlay)
    {
        m_beginPlay = true;
        beginPlay();
        initGameStages();
        startStages();
    }
}

void ly::World::tickInternal(float deltaTime)
{
    for (shared<Actor> actor : m_pendingActors)
    {
        m_actors.push_back(actor);
        actor->beginPlayInternal();
    }
    m_pendingActors.clear();

    for (auto iter = m_actors.begin(); iter != m_actors.end();)
    {
        iter->get()->tickInternal(deltaTime);
        iter++;
    }

    if (m_currentStage != m_gameStages.end())
    {
        m_currentStage->get()->tickStage(deltaTime);
    }

    tick(deltaTime);
}

void ly::World::render(sf::RenderWindow &window)
{
    for (shared<Actor> actor : m_actors)
    {
        actor->render(window);
    }
}

sf::Vector2u ly::World::getWindowSize() const
{
    return owningApp->getWindowSize();
}

void ly::World::cleanCycle()
{
    for (auto iter = m_actors.begin(); iter != m_actors.end();)
    {
        if (iter->get()->isPendingDistroyed())
        {
            iter = m_actors.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}

void ly::World::addStage(const shared<GameStage> &newStage)
{
    m_gameStages.push_back(newStage);
}

void ly::World::beginPlay()
{
    LOG("world begin play");
}

void ly::World::tick(float deltaTime)
{
    // LOG("world working at framerate: %f",1.f/deltaTime);
}

void ly::World::initGameStages()
{
}

void ly::World::nextGameStage()
{
    m_currentStage = m_gameStages.erase(m_currentStage);
    if (m_currentStage != m_gameStages.end())
    {
        m_currentStage->get()->startStage();
        m_currentStage->get()->onStageFinished.bindAction(getWeakRef(), &World::nextGameStage);
    }
    else
    {
        allGameStageFinished();
    }
}

void ly::World::allGameStageFinished()
{
    LOG("all stages finished");
}

void ly::World::startStages()
{
    m_currentStage = m_gameStages.begin();
    m_currentStage->get()->startStage();
    m_currentStage->get()->onStageFinished.bindAction(getWeakRef(), &World::nextGameStage);
}
