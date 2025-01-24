#include "level/gameLevelOne.hpp"
#include <framework/timerManager.hpp>
#include <framework/actor.hpp>
#include <framework/core.hpp>
#include "player/playerSpaceship.hpp"
#include "enemy/vanguard.hpp"

ly::GameLevelOne::GameLevelOne(Application *application) : World{application}
{
    testPlayerSpaceship = spawnAcotr<PlayerSpaceship>();
    testPlayerSpaceship.lock()->setActorLocation(sf::Vector2f(240, 320));

    weak<Vanguard> testSpaceship = spawnAcotr<Vanguard>();
    testSpaceship.lock()->setActorLocation(sf::Vector2f(300.f, 100.f));

}
void ly::GameLevelOne::beginPlay()
{
    TimerManager::get().setTimer(getWeakRef(),&GameLevelOne::timerCallBack_test,3.f,false);
}

void ly::GameLevelOne::timerCallBack_test()
{
    LOG("callback called");
}