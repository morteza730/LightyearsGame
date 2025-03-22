#include "level/mainMenuLevel.hpp"
#include <framework/core.hpp>
#include <framework/assetmanager.hpp>
#include "gameFramework/gameApplication.hpp"
#include "config.h"

ly::Application* getApplication()
{
    return new ly::GameApplication{};
}

namespace ly{
    GameApplication::GameApplication():
        Application{480,640,"light years",sf::Style::Titlebar|sf::Style::Close}
    {
        AssetManager::get().setAssetRootDir(get_resource());
        weak<World> world = loadWorld<MainMenuLevel>();
    }
}