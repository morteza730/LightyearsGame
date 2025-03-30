#pragma once

#include "gameplay/gamestage.hpp"

namespace ly
{
    class WaitStage: public GameStage
    {
        public:
            WaitStage(World *world, float waitDuration);
            virtual void startStage() override;

        private:
            float m_waitDuration;
    };
}