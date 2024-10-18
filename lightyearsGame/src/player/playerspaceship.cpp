#include "player/playerspaceship.hpp"
#include <SFML/System.hpp>
#include <framework/mathutility.hpp>
#include "weapon/bulletshooter.hpp"

ly::PlayerSpaceShip::PlayerSpaceShip(World *world, const std::string &texture_path):
SpaceShip(world,texture_path),
m_moveInput{},
m_speed{200.f},
m_shooter{new BulletShooter{this,0.1}}
{
}

ly::PlayerSpaceShip::~PlayerSpaceShip()
{
}

void ly::PlayerSpaceShip::tick(float deltaTime)
{
    SpaceShip::tick(deltaTime);
    handleInput();
    consumeInput();
}

void ly::PlayerSpaceShip::shoot()
{
    if (m_shooter){
        m_shooter->shoot();
    }
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
    clampInputOnEdge();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        shoot();
    }
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
}

void ly::PlayerSpaceShip::clampInputOnEdge()
{
    sf::Vector2f playerShipLocation = getActorLocation();
    sf::Vector2u windowSize = getWindowSize();
    if (playerShipLocation.x<=0 && m_moveInput.x<0){
        m_moveInput.x = 0;
    }
    if (playerShipLocation.x>=windowSize.x && m_moveInput.x>0){
        m_moveInput.x = 0;
    }
    if (playerShipLocation.y<=0 && m_moveInput.y<0){
        m_moveInput.y = 0;
    }
    if (playerShipLocation.y>=windowSize.y && m_moveInput.y>0){
        m_moveInput.y = 0;
    }
}
