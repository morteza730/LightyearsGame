#pragma once

#include "framework/core.hpp"
#include "framework/object.hpp"
#include <functional>

namespace ly
{
    struct Timer
    {
        public:
            Timer(weak<Object> obj, std::function<void()> callback, float duratioin,float repeat);
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
        void setTimer(weak<Object> obj, void(ClassName::*callback)(),float duration,bool repeat = false)
        {
            std::function<void()> callbackFunction = [obj, callback](){(static_cast<ClassName*>(obj.lock().get())->*callback)();};
            m_timers.push_back(Timer(obj,callbackFunction,duration,repeat));
        }
        void updateTimer(float deltaTime);

    protected:
        TimerManager();

    private:
        static unique<TimerManager> timerManager;
        List<Timer> m_timers;
    };
}