#pragma once

#include "widgets/widget.hpp"
#include "framework/core.hpp"
#include "framework/delegate.hpp"

namespace ly
{
    class Button : public Widget
    {
    public:
        Button(const std::string &text = "button",
               const std::string &texturePath = "PNG/UI/buttonBlue.png",
               const std::string &fontPath = "Bonus/kenvector_future.ttf");

        virtual sf::FloatRect getBound() const override;
        void setText(const std::string &text);
        void setCharacterSize(unsigned int size);
        virtual bool handleEvent(const sf::Event &event) override;
        Delegate<> onButtonClicked;

    private:
        virtual void draw(sf::RenderWindow &windowRef) override;
        virtual void locationUpdated(const sf::Vector2f &newLocation) override;
        virtual void rotationUpdated(float newRotation) override;
        void centerText();
        void buttonUp();
        void buttonDown();
        void mouseHover();

        shared<sf::Texture> m_texture;
        sf::Sprite m_sprite;

        shared<sf::Font> m_font;
        sf::Text m_text;

        sf::Color m_buttonDefaultColor;
        sf::Color m_buttonHoverColor;
        sf::Color m_buttonDownColor;

        bool m_isDown;
    };
}