#pragma once

#include <framework/world.hpp>
#include <framework/timermanager.hpp>

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
            virtual void initGameStages() override;
    };
}