#include "gameFramework/gameApplication.hpp"
#include <framework/world.hpp>
#include <framework/actor.hpp>
#include <framework/core.hpp>
#include "config.h"
#include "player/playerspaceship.hpp"
#include <framework/assetmanager.hpp>

ly::Application* getApplication()
{
    return new ly::GameApplication{};
}

namespace ly{
    GameApplication::GameApplication():
        Application{480,640,"light years",sf::Style::Titlebar|sf::Style::Close},
        counter{0.f}
    {
        AssetManager::get().setAssetRootDir(get_resource());
        weak<World> world = loadWorld<World>();
        shared<World> s_world = world.lock();
        s_world->spawnAcotr<Actor>();
        testPlayerSpaceShip = s_world->spawnAcotr<PlayerSpaceShip>();
        testPlayerSpaceShip.lock()->setActorLocation(sf::Vector2f(240,320));

        weak<Actor> testSpaceship = s_world->spawnAcotr<SpaceShip>();
        testSpaceship.lock()->setTexture("PNG/playerShip1_blue.png");
        testSpaceship.lock()->setActorLocation(sf::Vector2f(300.f,100.f));
        testSpaceship.lock()->setTeamID(2);
    }
}

void ly::GameApplication::tick(float deltaTime)
{
    counter += deltaTime;
    if (counter > 10.f)
    {
        if (!testPlayerSpaceShip.expired())
        {
            // testPlayerSpaceShip.lock()->distroy();
        }
    }
}
