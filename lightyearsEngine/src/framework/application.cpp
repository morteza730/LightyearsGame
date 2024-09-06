#include <iostream>
#include "framework/core.hpp"
#include "framework/application.hpp"
#include "framework/world.hpp"

ly::Application::Application(std::string title,unsigned int width,unsigned int height):
m_window(sf::VideoMode(width,height),title),
m_frameRate(float{60}),
m_tickClock(),
currentWorld(nullptr)
{}

ly::Application::Application():
m_window(sf::VideoMode(480,640),"light years"),
m_frameRate(float{60}),
m_tickClock()
{}

void ly::Application::run()
{
    float accumulatedTime{0};
    float deltaTime = 1.f/m_frameRate;
    m_tickClock.restart();
    while(m_window.isOpen()){
        sf::Event windowEvent;
        while(m_window.pollEvent(windowEvent)){
            if (windowEvent.type == sf::Event::EventType::Closed){
                m_window.close();
            }
        }
        float frameDeltatime = m_tickClock.restart().asSeconds();
        accumulatedTime += frameDeltatime;
        while(accumulatedTime>deltaTime){
            tick_internal(accumulatedTime);
            accumulatedTime -= deltaTime;
            render_internal();
        }
    }
}

void ly::Application::tick_internal(float deltaTime){
    tick(deltaTime);
    if (currentWorld){
        currentWorld->beginPlayInternal();
        currentWorld->tickInternal(deltaTime);
    }
}

void ly::Application::tick(float deltaTime){
    // std::cout<<(1/deltaTime)<<std::endl;
    //LOG("framerate per second is: %f",1/deltaTime);
}

void ly::Application::render_internal(){
    m_window.clear();
    render();
    m_window.display();
}

void ly::Application::render()
{
    sf::RectangleShape rec(sf::Vector2f(100,100));
    rec.setOrigin(50,50);
    rec.setPosition(m_window.getSize().x/2,m_window.getSize().y/2);
    rec.setFillColor(sf::Color::Yellow);
    m_window.draw(rec);
}