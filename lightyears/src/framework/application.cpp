#include "framework/application.hpp"

ly::Application::Application(std::string title,unsigned int width,unsigned int height):
m_window(sf::VideoMode(width,height),title)
{
}
void ly::Application::run()
{
    while(m_window.isOpen()){
        sf::Event windowEvent;
        while(m_window.pollEvent(windowEvent)){
            if (windowEvent.type == sf::Event::EventType::Closed){
                m_window.close();
            }
        }
    }
}