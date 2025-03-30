#pragma once

#include <widgets/hud.hpp>
#include <framework/delegate.hpp>
#include <widgets/button.hpp>
#include <widgets/textWidget.hpp>

namespace ly
{
    class MainMenuHUD : public HUD
    {
    public:
        MainMenuHUD();
        virtual void draw(sf::RenderWindow &windowRef) override;
        virtual bool handleEvent(const sf::Event& event);

        Delegate<> onStartButtonClicked;
        Delegate<> onQuitButtonClicked;

    private:
        virtual void init(const sf::RenderWindow &windowRef);
        void startButtonClicked();
        void quitButtonClicked();

        Button m_startButton;
        Button m_quitButton;
        TextWidget m_titleText;
    };
}