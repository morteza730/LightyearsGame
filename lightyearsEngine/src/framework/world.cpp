#include "framework/world.hpp"
#include "framework/core.hpp"
#include "framework/actor.hpp"
#include "framework/application.hpp"
#include "gameplay/gamestage.hpp"
#include "widgets/hud.hpp"

ly::World::World(Application *application)
    : m_beginPlay{false},
      m_owningApp{application},
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

    if (m_hud)
    {
        if (!m_hud->hasInit())
            m_hud->nativeInit(m_owningApp->getWindow());

        m_hud->tick(deltaTime);
    }
}

void ly::World::render(sf::RenderWindow &window)
{
    for (shared<Actor> actor : m_actors)
    {
        actor->render(window);
    }

    renderHud(window);
}

sf::Vector2u ly::World::getWindowSize() const
{
    return m_owningApp->getWindowSize();
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
    if (m_gameStages.empty())
        return;
    
    m_currentStage = m_gameStages.begin();
    m_currentStage->get()->startStage();
    m_currentStage->get()->onStageFinished.bindAction(getWeakRef(), &World::nextGameStage);
}

void ly::World::renderHud(sf::RenderWindow &window)
{
    if (!m_hud)
        return;

    m_hud->draw(window);
}

bool ly::World::dispatchEvent(const sf::Event &event)
{
    if (!m_hud)
        return false;

    return m_hud->handleEvent(event);
}
