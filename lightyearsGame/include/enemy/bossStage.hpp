#pragma once

#include "gameplay/gamestage.hpp"

namespace ly
{
    class Actor;
    class BossStage: public GameStage
    {
    public:
        BossStage(World *world);
        virtual void startStage() override;
    
    private:
        void bossDestroyed(Actor *bossActor);
    };
}