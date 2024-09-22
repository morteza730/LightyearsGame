#pragma once
#include <framework/application.hpp>
#include <framework/core.hpp>

namespace ly{
    class Actor;
    class SpaceShip;
    class GameApplication:public Application
    {
        public:
            GameApplication();
            void tick(float deltaTime);

        private:
            float counter;
            weak<SpaceShip> testPlayerSpaceShip;
    };
}