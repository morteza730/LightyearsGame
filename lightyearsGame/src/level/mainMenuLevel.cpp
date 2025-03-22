#include "level/mainMenuLevel.hpp"
#include "widgets/mainMenuHUD.hpp"
#include "level/gameLevelOne.hpp"
#include <framework/application.hpp>

ly::MainMenuLevel::MainMenuLevel(Application * application)
    :World{application}
{
    m_mainMenuHUD = spawnHUD<MainMenuHUD>();
}

void ly::MainMenuLevel::beginPlay()
{
    m_mainMenuHUD.lock()->onStartButtonClicked.bindAction(getWeakRef(), &MainMenuLevel::startGame);
    m_mainMenuHUD.lock()->onQuitButtonClicked.bindAction(getWeakRef(), &MainMenuLevel::quitGame);
}

void ly::MainMenuLevel::startGame()
{
    getApplication()->loadWorld<GameLevelOne>();
}

void ly::MainMenuLevel::quitGame()
{
   getApplication()->quitApplication();
}
