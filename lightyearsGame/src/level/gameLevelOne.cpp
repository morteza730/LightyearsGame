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
#include "player/playerManager.hpp"
#include "widgets/gameplayHUD.hpp"
#include "enemy/chaosStage.hpp"
#include "enemy/bossStage.hpp"

ly::GameLevelOne::GameLevelOne(Application *application) : World{application}
{
}

void ly::GameLevelOne::beginPlay()
{
    Player &newPlayer = PlayerManager::get().createNewPlayer();
    m_playerSpaceship = newPlayer.spawnSpaceShip(this);
    m_playerSpaceship.lock()->onActorDestoryed.bindAction(getWeakRef(), &GameLevelOne::handleSpaceshipDestruction);
    m_gameplayHud = spawnHUD<GameplayHUD>();
}

void ly::GameLevelOne::initGameStages()
{
    addStage(shared<BossStage>{new BossStage{this}});

    addStage(shared<WaitStage>{new WaitStage{this, 5.f}});
    addStage(shared<VanguardStage>{new VanguardStage{this}});

    addStage(shared<WaitStage>{new WaitStage{this, 15.f}});
    addStage(shared<HexagonStage>{new HexagonStage{this}});

    addStage(shared<WaitStage>{new WaitStage{this, 12.f}});
    addStage(shared<TwinBladeStage>{new TwinBladeStage{this}});

    addStage(shared<WaitStage>{new WaitStage{this, 10.f}});
    addStage(shared<UFOStage>(new UFOStage{this}));

    addStage(shared<WaitStage>{new WaitStage{this, 8.f}});
    addStage(shared<ChaosStage>{new ChaosStage{this}});
}

void ly::GameLevelOne::handleSpaceshipDestruction(Actor *destroyedSpaceship)
{
    m_playerSpaceship = PlayerManager::get().getPlayer()->spawnSpaceShip(this);

    if (m_playerSpaceship.expired())
        gameOver();
    else
        m_playerSpaceship.lock()->onActorDestoryed.bindAction(getWeakRef(), &GameLevelOne::handleSpaceshipDestruction);
}

void ly::GameLevelOne::gameOver()
{
    LOG("GAME OVER ..............................");
}