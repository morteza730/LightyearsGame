#include "player/playerspaceship.hpp"
#include <SFML/System.hpp>
#include <framework/mathutility.hpp>

ly::PlayerSpaceShip::PlayerSpaceShip(World *world, const std::string &texture_path):
SpaceShip(world,texture_path),
m_moveInput{},
m_speed{100.f}
{
}

void ly::PlayerSpaceShip::tick(float deltaTime)
{
    SpaceShip::tick(deltaTime);
    handleInput();
    consumeInput();
}

void ly::PlayerSpaceShip::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        m_moveInput.y = -1.f;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        m_moveInput.y = 1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        m_moveInput.x = -1.f;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        m_moveInput.x = 1.f;
    }
    normalizeInput(m_moveInput);
    // getActorLocation();
}

void ly::PlayerSpaceShip::consumeInput()
{
    setVelocity(m_moveInput*m_speed);
    m_moveInput.x = 0;
    m_moveInput.y = 0;
}

void ly::PlayerSpaceShip::normalizeInput(sf::Vector2f& vector)
{
    normalize(vector);
    LOG("move input is %f, and %f",vector.x,vector.y);
}
