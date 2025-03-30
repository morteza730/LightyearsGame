#include "widgets/gameplayHUD.hpp"
#include "player/playerManager.hpp"
#include "player/playerspaceship.hpp"

ly::GameplayHUD::GameplayHUD()
    : m_framerateText{"Frame Rate is: "},
      m_playerHealthBar{},
      m_playerLifeIcon{"PNG/UI/playerLife1_blue.png"},
      m_playerLifeCount{""},
      m_playerScoreIcon{"PNG/Power-ups/star_gold.png"},
      m_playerScoreCount{""},
      m_healthyHealthColor{sf::Color{128, 255, 128, 255}},
      m_criticalHealthColor{sf::Color{255, 128, 128, 255}},
      m_criticalHealthThreshold{0.3f},
      m_widgetSpacing{10.f}
{
    m_framerateText.setCharacterSize(20);
    m_playerLifeCount.setCharacterSize(20);
    m_playerScoreCount.setCharacterSize(20);
}

void ly::GameplayHUD::draw(sf::RenderWindow &windowRef)
{
    m_framerateText.nativeDraw(windowRef);
    m_playerHealthBar.nativeDraw(windowRef);
    m_playerLifeIcon.nativeDraw(windowRef);
    m_playerLifeCount.nativeDraw(windowRef);
    m_playerScoreIcon.nativeDraw(windowRef);
    m_playerScoreCount.nativeDraw(windowRef);
}
void ly::GameplayHUD::tick(float deltaTime)
{
    int framerate = int(1 / deltaTime);
    std::string framerateStr = "Frame Rate is: " + std::to_string(framerate);
    m_framerateText.setString(framerateStr);
}

void ly::GameplayHUD::init(const sf::RenderWindow &windowRef)
{
    auto windowSize = windowRef.getSize();
    m_playerHealthBar.setLocation({20.f, windowSize.y - 40.f});

    sf::Vector2f nextWidgetPos = m_playerHealthBar.getLocation();

    nextWidgetPos += sf::Vector2f(m_playerHealthBar.getBound().width + m_widgetSpacing, 0.f);
    m_playerLifeIcon.setLocation(nextWidgetPos);

    nextWidgetPos += sf::Vector2f(m_playerLifeIcon.getBound().width + m_widgetSpacing, 0.f);
    m_playerLifeCount.setLocation(nextWidgetPos);

    nextWidgetPos += sf::Vector2f(m_playerLifeCount.getBound().width + m_widgetSpacing * 4, -m_widgetSpacing / 2.f);
    m_playerScoreIcon.setLocation(nextWidgetPos);

    nextWidgetPos += sf::Vector2f(m_playerScoreIcon.getBound().width + m_widgetSpacing, m_widgetSpacing / 2.f);
    m_playerScoreCount.setLocation(nextWidgetPos);

    refreshHealthBar();
    connectPlayerStats();
}

void ly::GameplayHUD::updateHeathBar(float amt, float currentHealth, float maxHealth)
{
    m_playerHealthBar.updateValue(currentHealth, maxHealth);
    if (currentHealth / maxHealth > m_criticalHealthThreshold)
    {
        m_playerHealthBar.setForegroundColor(m_healthyHealthColor);
    }
    else
    {
        m_playerHealthBar.setForegroundColor(m_criticalHealthColor);
    }
}

void ly::GameplayHUD::refreshHealthBar()
{
    weak<PlayerSpaceship> playerSpaceship = PlayerManager::get().getPlayer()->getCurrentSpaceship();
    if (!playerSpaceship.expired())
    {
        playerSpaceship.lock()->onActorDestoryed.bindAction(getWeakRef(), &GameplayHUD::restartPlayerHealth);
        HealthComponent &healthComp = playerSpaceship.lock()->getHealthComponent();
        healthComp.onHealthChanged.bindAction(getWeakRef(), &GameplayHUD::updateHeathBar);
        updateHeathBar(0.f, healthComp.getHealth(), healthComp.getMaxHealth());
    }
}

void ly::GameplayHUD::restartPlayerHealth(Actor *actor)
{
    refreshHealthBar();
}

void ly::GameplayHUD::connectPlayerStats()
{
    Player *player = PlayerManager::get().getPlayer();

    if (!player)
        return;

    int lifeCount = player->getLifeCount();
    m_playerLifeCount.setString(std::to_string(lifeCount));
    player->onLifeCountChanged.bindAction(getWeakRef(), &GameplayHUD::playerLifeCountUpdated);

    int scoreCount = player->getScore();
    m_playerScoreCount.setString(std::to_string(scoreCount));
    player->onScoreChanged.bindAction(getWeakRef(), &GameplayHUD::playerScoreCountUpdated);
}

void ly::GameplayHUD::playerLifeCountUpdated(int amt)
{
    m_playerLifeCount.setString(std::to_string(amt));
}

void ly::GameplayHUD::playerScoreCountUpdated(int amt)
{
    m_playerScoreCount.setString(std::to_string(amt));
}

bool ly::GameplayHUD::handleEvent(const sf::Event &event)
{
    return HUD::handleEvent(event);
}
