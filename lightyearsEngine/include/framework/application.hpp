#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "framework/core.hpp"

namespace ly{
    class World;
    class Application{
        public:
            Application(std::string title,unsigned int width,unsigned int height);
            Application();
            virtual void run();

            template<typename worldType>
            weak<worldType> loadWorld();

        private:
            sf::RenderWindow m_window;
            float m_frameRate;
            sf::Clock m_tickClock;
            void render_internal();
            void tick_internal(float deltaTime);
            virtual void render();
            virtual void tick(float deltaTime);
            shared<World> currentWorld;
    };
    template<typename worldType>
    weak<worldType> Application::loadWorld(){
        shared<worldType> newWorld{new worldType{this}};
        currentWorld = newWorld;
        return newWorld;
    }
}