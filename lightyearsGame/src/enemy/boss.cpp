#include "enemy/boss.hpp"
#include "gameplay/healthComponent.hpp"

ly::Boss::Boss(World *world)
    : EnemySpaceship{world, "PNG/Enemies/boss.png"},
      m_speed{100.f},
      m_baseSpeed{100.f},
      m_switchDistanceToEdge{100.f},
      m_baseShooterRight{this, 1.f, {-50.f, 55.f}, 180.f},
      m_baseShooterLeft{this, 1.f, {-50.f, -55.f}, 180.f},
      m_threewayShooter{this, 4.f, {-100.f, 0.f}, 180.f},
      m_frontalWiperRight{this, 5.f, {-50.f, 100.f}, 180.f},
      m_frontalWiperLeft{this, 5.f, {-50.f, -100.f}, 180.f},
      m_finalShooterRight{this, 0.3f, {-50.f, 150.f}, 180.f},
      m_finalShooterLeft{this, 0.3f, {-50.f, -150.f}, 180.f},
      m_stage{1}
{
    setVelocity({m_speed, 0.f});
    setRewardSpawnWeight(0.f);
}

void ly::Boss::tick(float deltaTime)
{
    EnemySpaceship::tick(deltaTime);
    shootBaseShooters();
    shootThreeWayShooter();
    shootFrontalWiper();
    if (m_stage == 4)
    {
        shootFinalShooter();
    }
    checkMove();
}

void ly::Boss::beginPlay()
{
    EnemySpaceship::beginPlay();
    HealthComponent &healthComp = getHealthComponent();
    healthComp.setInitialHealth(3000.f, 3000.f);
    healthComp.onHealthChanged.bindAction(getWeakRef(),healthChanged);
}

void ly::Boss::checkMove()
{
    if (getActorLocation().x > getWindowSize().x - m_switchDistanceToEdge)
    {
        setVelocity({-m_speed, 0.f});
    }
    else if (getActorLocation().x < m_switchDistanceToEdge)
    {
        setVelocity({m_speed, 0.f});
    }
}

void ly::Boss::shootBaseShooters()
{
    m_baseShooterLeft.shoot();
    m_baseShooterRight.shoot();
}

void ly::Boss::shootThreeWayShooter()
{
    m_threewayShooter.shoot();
}

void ly::Boss::shootFrontalWiper()
{
    m_frontalWiperLeft.shoot();
    m_frontalWiperRight.shoot();
}

void ly::Boss::shootFinalShooter()
{
    m_finalShooterLeft.shoot();
    m_finalShooterRight.shoot();
}

void ly::Boss::healthChanged(float amt, float currentHealth, float maxHealth)
{
    float percentageLeft = currentHealth/maxHealth;
    if (percentageLeft < 0.7 && percentageLeft > 0.5)
    {
        setStage(2);
    }

    if (percentageLeft < 0.5 && percentageLeft > 0.3)
    {
        setStage(3);
    }

    if (percentageLeft < 0.3)
    {
        setStage(4);
    }
}

void ly::Boss::setStage(int newStage)
{
    m_stage = newStage;
    m_baseShooterLeft.setCurrentLevel(m_stage);
    m_baseShooterRight.setCurrentLevel(m_stage);
    m_threewayShooter.setCurrentLevel(m_stage);
    m_frontalWiperLeft.setCurrentLevel(m_stage);
    m_frontalWiperRight.setCurrentLevel(m_stage);
    m_speed = m_stage * m_baseSpeed;
}
