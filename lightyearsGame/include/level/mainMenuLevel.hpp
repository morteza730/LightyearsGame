#pragma once

#include <framework/world.hpp>

namespace ly
{
    class MainMenuHUD;
    class MainMenuLevel: public World
    {
        public:
            MainMenuLevel(Application *application);
            virtual void beginPlay() override; 

        private:
            weak<MainMenuHUD> m_mainMenuHUD;
            void startGame();
            void quitGame();
    };
}