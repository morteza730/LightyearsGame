#include "gameFramework/gameApplication.hpp"
#include <framework/world.hpp>
#include <framework/actor.hpp>
#include <framework/core.hpp>
#include "config.h"

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
        actorToDistroy = s_world->spawnAcotr<Actor>();
        actorToDistroy.lock()->setTexture(get_resource()+"PNG/playerShip1_blue.png");
        actorToDistroy.lock()->setActorLocation(sf::Vector2f(240,320));
        actorToDistroy.lock()->setActorRotation(90.f);
    }
}

void ly::GameApplication::tick(float deltaTime)
{
    counter += deltaTime;
    if (counter>2.f){
        if (!actorToDistroy.expired()){
            actorToDistroy.lock()->distroy();
        }
    }
}
