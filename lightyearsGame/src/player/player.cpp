#include "player/player.hpp"
#include <framework/world.hpp>
#include "player/playerspaceship.hpp"

ly::Player::Player()
    : m_lifeCount{3},
      m_score{0},
      m_currentSpaceship{}
{
}

ly::weak<ly::PlayerSpaceship> ly::Player::spawnSpaceShip(World *world)
{
    if (m_lifeCount == 0)
    {
        onLifeExhausted.broadCast();
        return weak<ly::PlayerSpaceship>{};
    }

    m_lifeCount--;
    onLifeCountChanged.broadCast(m_lifeCount);

    m_currentSpaceship = world->spawnAcotr<PlayerSpaceship>();

    auto windowSize = world->getWindowSize();
    m_currentSpaceship.lock()->setActorLocation(sf::Vector2f(windowSize.x/2.f, windowSize.y - 100));
    
    return m_currentSpaceship;
}

void ly::Player::addLifeCount(unsigned int amt)
{
    m_lifeCount += amt;
    onLifeCountChanged.broadCast(m_lifeCount);
}

void ly::Player::addScore(unsigned int amt)
{
    m_score += amt;
    onScoreChanged.broadCast(m_score);
}
