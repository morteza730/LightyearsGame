#pragma once

#include <sfml/Graphics.hpp>
#include "gameplay/gamestage.hpp"
#include <framework/timermanager.hpp>

namespace ly
{
    class VanguardStage : public GameStage
    {
    public:
        VanguardStage(World *world);
        virtual void startStage() override;

    private:
        virtual void stageFinished() override;
        void spawnVanguard();
        void switchRow();

        float m_spawnInterval;
        float m_switchInterval;
        float m_spawnDistanceToEdge;

        sf::Vector2f m_leftSpawnLocation;
        sf::Vector2f m_rightSpawnLocation;
        sf::Vector2f m_spawnLocation;

        TimerHandle m_spawnTimerHandle;
        TimerHandle m_switchTimerHandle;

        int m_rowsToSpawn;
        int m_rowSpawnCount;

        int m_vanguardsPerRow;
        int m_vanguardSpawnCount;
    };
}