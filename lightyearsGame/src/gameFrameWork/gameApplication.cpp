#include "gameFramework/gameApplication.hpp"
#include <framework/world.hpp>
#include <framework/actor.hpp>
#include <framework/core.hpp>

ly::Application* getApplication()
{
    return new ly::GameApplication{};
}

namespace ly{
    GameApplication::GameApplication():
        counter{0}
    {
        weak<World> world = loadWorld<World>();
        shared<World> s_world = world.lock();
        s_world->spawnAcotr<Actor>();
        actorToDistroy = s_world->spawnAcotr<Actor>();
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
