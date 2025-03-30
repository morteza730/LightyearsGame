#pragma once

#include <sfml/Graphics.hpp>
#include <gameplay/gamestage.hpp>
#include <framework/timermanager.hpp>

namespace ly
{
    class UFOStage : public GameStage
    {
    public:
        UFOStage(World *world);
        virtual void startStage() override;

    private:
        virtual void stageFinished() override;
        sf::Vector2f getRandomLocation() const;
        void spawnUFO();

        float m_spawnInterval;
        int m_spawnAmt;
        int m_spawnCount;
        float m_UFOSpeed;

        TimerHandle m_spawnTimerHandle;
    };
}
