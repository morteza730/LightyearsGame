#pragma once

#include "framework/object.hpp"
#include "framework/delegate.hpp"

namespace ly
{
    class World;
    class GameStage : public Object
    {
    public:
        GameStage(World *world);
        const World *getWorld() const { return m_world; }
        World *getWorld() {return m_world;}

        Delegate<> onStageFinished;

        virtual void startStage();
        virtual void tickStage(float deltaTime);
        void finishStage();
        bool isStageFinished() const {return m_stageFinished;}

    private:
        World *m_world;
        bool m_stageFinished;
        virtual void stageFinished();

    };
}