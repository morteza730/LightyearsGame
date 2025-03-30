#include "player/playerManager.hpp"

namespace ly
{
    unique<PlayerManager> PlayerManager::playerManager{nullptr};
}

ly::PlayerManager::PlayerManager()
    : m_players{}
{
}

ly::PlayerManager &ly::PlayerManager::get()
{
    if (!playerManager)
        playerManager = unique<PlayerManager>{new PlayerManager{}};

    return *playerManager;
}

ly::Player &ly::PlayerManager::createNewPlayer()
{
    m_players.emplace(m_players.begin(), Player());
    return m_players.back();
}

const ly::Player *ly::PlayerManager::getPlayer(int index) const
{
    if (index >= m_players.size() || index < 0)
        return nullptr;

    return &(m_players.at(index));
}

ly::Player *ly::PlayerManager::getPlayer(int index)
{
    if (index >= m_players.size() || index < 0)
        return nullptr;

    return &(m_players.at(index));
}