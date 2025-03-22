#pragma once

#include <widgets/hud.hpp>
#include <widgets/textWidget.hpp>
#include <widgets/valueGuage.hpp>
#include <widgets/imageWidget.hpp>
#include <widgets/button.hpp>

namespace ly
{
    class Actor;
    class GameplayHUD : public HUD
    {
    public:
        GameplayHUD();
        virtual void draw(sf::RenderWindow &windowRef) override;
        virtual void tick(float deltaTime) override;
        virtual bool handleEvent(const sf::Event& event);

    private:
        virtual void init(const sf::RenderWindow &windowRef);
        void updateHeathBar(float amt, float currentHealth,float maxHealth);
        void refreshHealthBar();
        void restartPlayerHealth(Actor *actor);
        void connectPlayerStats();
        void playerLifeCountUpdated(int amt);
        void playerScoreCountUpdated(int amt);
        
        TextWidget m_framerateText;
        ValueGuage m_playerHealthBar;
        ImageWidget m_playerLifeIcon;
        TextWidget m_playerLifeCount;
        ImageWidget m_playerScoreIcon;
        TextWidget m_playerScoreCount;

        sf::Color m_healthyHealthColor;
        sf::Color m_criticalHealthColor;
        float m_criticalHealthThreshold;
        float m_widgetSpacing;
    };
}