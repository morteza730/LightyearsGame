#include "framework/timermanager.hpp"

namespace ly
{
    unique<TimerManager> TimerManager::timerManager{nullptr};
}

ly::Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duratioin, float repeat)
    : m_listener{weakRef, callback},
      m_duration{duratioin},
      m_repeat{repeat},
      m_timeCounter{0.f},
      m_isExpired{false}
{
}

void ly::Timer::tickTime(float deltaTime)
{
    if (expired())
        return;

    m_timeCounter += deltaTime;

    if (m_timeCounter < m_duration)
        return;

    m_listener.second();

    if (m_repeat)
    {
        m_timeCounter = 0.f;
    }
    else
    {
        setExpired();
    }
}

bool ly::Timer::expired() const
{
    return m_isExpired || m_listener.first.expired() || m_listener.first.lock() -> isPendingDistroyed();
}

void ly::Timer::setExpired()
{
    m_isExpired = true;
}

ly::TimerManager::TimerManager()
{
}

void ly::TimerManager::updateTimer(float deltaTime)
{
    for (Timer& timer: m_timers)
    {
        timer.tickTime(deltaTime);
    }
}

ly::TimerManager &ly::TimerManager::get()
{
    if (!timerManager)
    {
        timerManager = std::move(unique<TimerManager>(new TimerManager{}));
    }
    return *timerManager;
}