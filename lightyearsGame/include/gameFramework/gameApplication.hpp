#pragma once
#include <framework/application.hpp>
#include <framework/core.hpp>

namespace ly{
    class PlayerSpaceShip;
    class GameApplication:public Application
    {
        public:
            GameApplication();
            void tick(float deltaTime);

        private:
            float counter;
            weak<PlayerSpaceShip> testPlayerSpaceShip;
    };
}