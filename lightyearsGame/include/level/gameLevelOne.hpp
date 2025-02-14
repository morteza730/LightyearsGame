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
            weak<PlayerSpaceship> m_playerSpaceship;
            virtual void initGameStages() override;
            void handleSpaceshipDestruction(Actor *destroyedSpaceship);
            void gameOver();
    };
}