#pragma once

#include <framework/core.hpp>
#include "player/player.hpp"

namespace ly
{
    class PlayerManager
    {
    public:
        Player &createNewPlayer();
        const Player *getPlayer(int index = 0) const;
        Player *getPlayer(int index = 0);
        static PlayerManager& get();

    protected:
        PlayerManager();

    private:
        List<Player> m_players;
        static unique<PlayerManager> playerManager;
    };
}