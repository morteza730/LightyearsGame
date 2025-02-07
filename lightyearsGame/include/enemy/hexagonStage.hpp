#pragma once

#include <sfml/Graphics.hpp>
#include <gameplay/gamestage.hpp>
#include <framework/timermanager.hpp>

namespace ly
{
    class HexagonStage : public GameStage
    {
    public:
        HexagonStage(World *world);
        virtual void startStage() override;

    private:
        virtual void stageFinished() override;
        void spawnHexagon();

        float m_spawnInterval;
        float m_spawnSideDistance;

        sf::Vector2f m_leftSpawnLocation;
        sf::Vector2f m_rightSpawnLocation;
        sf::Vector2f m_middleSpawnLocation;

        TimerHandle m_spawnTimerHandle;

        int m_spawnGroundAmt;
        int m_spawnGroundCount;
    };
}