#pragma once

#include <framework/world.hpp>
#include <framework/timermanager.hpp>

namespace ly
{
    class PlayerSpaceship;
    class GameplayHUD;
    class GameLevelOne: public World
    {
        public:
            GameLevelOne(Application *application);

        private:
            virtual void beginPlay() override;
            weak<PlayerSpaceship> m_playerSpaceship;
            weak<GameplayHUD> m_gameplayHud;
            virtual void initGameStages() override;
            void handleSpaceshipDestruction(Actor *destroyedSpaceship);
            void gameOver();
    };
}