#pragma once

#include <sfml/Graphics.hpp>
#include "gameplay/gamestage.hpp"
#include <framework/timermanager.hpp>

namespace ly
{
    class TwinBladeStage : public GameStage
    {
    public:
        TwinBladeStage(World *world);
        virtual void startStage() override;

    private:
        virtual void stageFinished() override;
        void spawnTwinBlade();

        float m_spawnInterval;
        float m_spawnDistanceToEdge;

        sf::Vector2f m_leftSpawnLocation;
        sf::Vector2f m_rightSpawnLocation;
        sf::Vector2f m_spawnLocation;

        TimerHandle m_spawnTimerHandle;

        int m_spawnAmt;
        int m_spawnCount;
    };
}