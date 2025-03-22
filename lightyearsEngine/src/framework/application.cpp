#include <iostream>
#include "framework/core.hpp"
#include "framework/application.hpp"
#include "framework/world.hpp"
#include "framework/assetmanager.hpp"
#include "framework/physicssystem.hpp"
#include "framework/timermanager.hpp"

ly::Application::Application(unsigned int width, unsigned int height, std::string title, sf::Uint32 style)
    : m_window(sf::VideoMode(width, height), title, style),
      m_frameRate(float{60}),
      m_tickClock(),
      m_currentWorld(nullptr),
      m_cleanCycleClock{},
      m_cleanCycleInterval{2.f}
{
}

void ly::Application::run()
{
    float accumulatedTime{0};
    float deltaTime = 1.f / m_frameRate;
    m_tickClock.restart();
    while (m_window.isOpen())
    {
        sf::Event windowEvent;
        while (m_window.pollEvent(windowEvent))
        {
            if (windowEvent.type == sf::Event::EventType::Closed)
            {
                quitApplication();
            }
            else
            {
                dispatchEvent(windowEvent);
            }
        }
        float frameDeltatime = m_tickClock.restart().asSeconds();
        accumulatedTime += frameDeltatime;
        while (accumulatedTime > deltaTime)
        {
            tick_internal(accumulatedTime);
            accumulatedTime -= deltaTime;
            render_internal();
        }
    }
}

sf::Vector2u ly::Application::getWindowSize()
{
    return m_window.getSize();
}

void ly::Application::tick_internal(float deltaTime)
{
    tick(deltaTime);
    if (m_currentWorld)
    {
        m_currentWorld->beginPlayInternal();
        m_currentWorld->tickInternal(deltaTime);
    }

    TimerManager::get().updateTimer(deltaTime);

    PhysicsSystem::get().step(deltaTime);
    // clean cycle
    if (m_cleanCycleClock.getElapsedTime().asSeconds() > m_cleanCycleInterval)
    {
        m_cleanCycleClock.restart();
        AssetManager::get().cleanCycle();
        if (m_currentWorld)
        {
            m_currentWorld->cleanCycle();
        }
    }
    if (m_pendingWorld && m_pendingWorld != m_currentWorld)
    {
        m_currentWorld = m_pendingWorld;
        m_currentWorld -> beginPlayInternal();
    }
}

void ly::Application::tick(float deltaTime)
{
    // LOG("framerate per second is: %f",1/deltaTime);
}

void ly::Application::quitApplication()
{
    getWindow().close();
}

bool ly::Application::dispatchEvent(const sf::Event &event)
{
    if (!m_currentWorld)
        return false;
    
    return m_currentWorld->dispatchEvent(event);
}

void ly::Application::render_internal()
{
    m_window.clear();
    render();
    m_window.display();
}

void ly::Application::render()
{
    if (m_currentWorld)
    {
        m_currentWorld->render(m_window);
    }
}