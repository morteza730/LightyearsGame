#pragma once

#include "gameplay/gamestage.hpp"
#include <framework/timermanager.hpp>
#include <sfml/Graphics.hpp>

namespace ly
{
    class ChaosStage : public GameStage
    {
    public:
        ChaosStage(World *world);
        virtual void startStage() override;

    private:
        virtual void stageFinished() override;
        void spawnVanguard();
        void spawnTwinBlade();
        void spawnHexegon();
        void spawnUFO();

        void increaseDifficulty();
        void stageDurationReached();

        sf::Vector2f getRandomeSpawnLocationTop();
        sf::Vector2f getRandomeSpawnLocationSide();

        float m_spawnInterval;
        float m_minSpawnInterval;

        float m_spawnIntervalDecrement;
        float m_spawnIntervalDecrementInterval;

        float m_stageDuration;

        TimerHandle m_dificultyTimer;
        TimerHandle m_spawnTimer;
    };
};