#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "framework/core.hpp"

namespace ly
{
    class World;
    class Application
    {
    public:
        Application(unsigned int width, unsigned int height, std::string title, sf::Uint32 style);
        virtual void run();
        sf::Vector2u getWindowSize();
        template <typename worldType>
        weak<worldType> loadWorld();
        sf::RenderWindow &getWindow() { return m_window; }
        const sf::RenderWindow &getWindow() const { return m_window; }
        void quitApplication();

    private:
        bool dispatchEvent(const sf::Event &event);
        sf::RenderWindow m_window;
        float m_frameRate;
        sf::Clock m_tickClock;
        void render_internal();
        void tick_internal(float deltaTime);
        virtual void render();
        virtual void tick(float deltaTime);
        shared<World> m_currentWorld;
        shared<World> m_pendingWorld;
        sf::Clock m_cleanCycleClock;
        float m_cleanCycleInterval;
    };
    template <typename worldType>
    weak<worldType> Application::loadWorld()
    {
        shared<worldType> newWorld{new worldType{this}};
        m_pendingWorld = newWorld;
        return newWorld;
    }
}