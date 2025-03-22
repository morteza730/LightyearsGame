#include "enemy/bossStage.hpp"
#include "enemy/boss.hpp"
#include <framework/world.hpp>

ly::BossStage::BossStage(World *world)
    : GameStage{world}
{
}

void ly::BossStage::startStage()
{
    weak<Boss> boss = getWorld()->spawnAcotr<Boss>();
    auto windowSize = getWorld()->getWindowSize();
    boss.lock()->setActorLocation({windowSize.x / 2.f, 100.f});
    boss.lock()->onActorDestoryed.bindAction(getWeakRef(), &BossStage::bossDestroyed);
}

void ly::BossStage::bossDestroyed(Actor *bossActor)
{
    finishStage();
}
