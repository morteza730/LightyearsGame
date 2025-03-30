#pragma once

#include "framework/core.hpp"
#include "framework/object.hpp"
#include <functional>

namespace ly
{
    struct TimerHandle
    {
    public:
        TimerHandle();
        unsigned int getTimerKey() const { return m_timerKey; }

    private:
        unsigned int m_timerKey;
        static unsigned int timerKeyCounter;
        static unsigned int getNextTimerKey() { return ++timerKeyCounter; }
    };

    struct TimerHandleHasher
    {
    public:
        std::size_t operator()(const TimerHandle &timeHandle) const
        {
            return timeHandle.getTimerKey();
        }
    };

    bool operator==(const TimerHandle &lhs, const TimerHandle &rhs);

    struct Timer
    {
    public:
        Timer(weak<Object> obj, std::function<void()> callback, float duratioin, float repeat);
        void tickTime(float deltaTime);
        bool expired() const;
        void setExpired();

    private:
        std::pair<weak<Object>, std::function<void()>> m_listener;
        float m_duration;
        float m_repeat;
        float m_timeCounter;
        bool m_isExpired;
    };

    class TimerManager
    {
    public:
        static TimerManager &get();
        template <typename ClassName>
        TimerHandle setTimer(weak<Object> obj, void (ClassName::*callback)(), float duration, bool repeat = false)
        {
            TimerHandle newHandle{};
            std::function<void()> callbackFunction = [obj, callback]()
            { (static_cast<ClassName *>(obj.lock().get())->*callback)(); };
            m_timers.insert({newHandle, Timer(obj, callbackFunction, duration, repeat)});
            return newHandle;
        }
        void clearTimer(TimerHandle timerHandle);
        void updateTimer(float deltaTime);

    protected:
        TimerManager();

    private:
        static unique<TimerManager> timerManager;
        Dictionary<TimerHandle, Timer, TimerHandleHasher> m_timers;
    };
}