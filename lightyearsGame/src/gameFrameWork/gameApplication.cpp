#include "gameFramework/gameApplication.hpp"
#include <framework/world.hpp>
#include <framework/actor.hpp>
#include <framework/core.hpp>
#include "config.h"
#include "spaceship/spaceship.hpp"

ly::Application* getApplication()
{
    return new ly::GameApplication{};
}

namespace ly{
    GameApplication::GameApplication():
        Application{480,640,"light years",sf::Style::Titlebar|sf::Style::Close},
        counter{0}
    {
        weak<World> world = loadWorld<World>();
        shared<World> s_world = world.lock();
        s_world->spawnAcotr<Actor>();
        testPlayerSpaceShip = s_world->spawnAcotr<SpaceShip>();
        testPlayerSpaceShip.lock()->setTexture(get_resource()+"PNG/playerShip1_blue.png");
        testPlayerSpaceShip.lock()->setActorLocation(sf::Vector2f(240,320));
        // testPlayerSpaceShip.lock()->setActorRotation(90.f);
        testPlayerSpaceShip.lock()->setVelocity(sf::Vector2f(0.f,-40.f));
    }
}

void ly::GameApplication::tick(float deltaTime)
{
    // counter += deltaTime;
    // if (counter>2.f){
    //     if (!testPlayerSpaceShip.expired()){
    //         testPlayerSpaceShip.lock()->distroy();
    //     }
    // }
    testPlayerSpaceShip.lock()->tick(deltaTime);
}
