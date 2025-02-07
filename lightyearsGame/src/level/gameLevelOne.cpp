#include "level/gameLevelOne.hpp"
#include <framework/timerManager.hpp>
#include <framework/actor.hpp>
#include <framework/core.hpp>
#include "enemy/vanguardStage.hpp"
#include "enemy/twinBladeStage.hpp"
#include "enemy/hexagonStage.hpp"
#include "enemy/ufoStage.hpp"
#include <gameplay/waitstage.hpp>
#include <gameplay/gamestage.hpp>
#include "player/playerSpaceship.hpp"

ly::GameLevelOne::GameLevelOne(Application *application) : World{application}
{
    testPlayerSpaceship = spawnAcotr<PlayerSpaceship>();
    testPlayerSpaceship.lock()->setActorLocation(sf::Vector2f(240, 320));
}
void ly::GameLevelOne::beginPlay()
{
}

void ly::GameLevelOne::initGameStages()
{
    addStage(shared<WaitStage>{new WaitStage{this, 5.f}});
    addStage(shared<UFOStage>(new UFOStage{this}));

    addStage(shared<WaitStage>{new WaitStage{this, 5.f}});
    addStage(shared<VanguardStage>{new VanguardStage{this}});

    addStage(shared<WaitStage>{new WaitStage{this, 5.f}});
    addStage(shared<HexagonStage>{new HexagonStage{this}});

    addStage(shared<WaitStage>{new WaitStage{this, 5.f}});
    addStage(shared<TwinBladeStage>{new TwinBladeStage{this}});
}