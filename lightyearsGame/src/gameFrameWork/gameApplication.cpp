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
        counter{0}
    {
        AssetManager::get().setAssetRootDir(get_resource());
        weak<World> world = loadWorld<World>();
        shared<World> s_world = world.lock();
        s_world->spawnAcotr<Actor>();
        testPlayerSpaceShip = s_world->spawnAcotr<PlayerSpaceShip>();
        testPlayerSpaceShip.lock()->setActorLocation(sf::Vector2f(240,320));
    }
}

void ly::GameApplication::tick(float deltaTime)
{
    
}
