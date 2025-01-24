#pragma once

#include <framework/world.hpp>

namespace ly
{
    class PlayerSpaceship;
    class GameLevelOne: public World
    {
        public:
            GameLevelOne(Application *application);

        private:
            virtual void beginPlay() override;
            weak<PlayerSpaceship> testPlayerSpaceship;
            void timerCallBack_test();
    };
}