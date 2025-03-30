#pragma once

#include "widgets/widget.hpp"

namespace ly
{
    class ValueGuage : public Widget
    {
    public:
        ValueGuage(
            const sf::Vector2f &size = sf::Vector2f{200.f, 24.f},
            float initialPercent = 0.75f,
            const sf::Color foregroundColor = sf::Color{128, 255, 128, 255},
            const sf::Color backgroundColor = sf::Color{128, 128, 128, 255});
        void updateValue(float value, float maxValue);
        virtual sf::FloatRect getBound() const override;
        void setTextSize(unsigned int characterSize);
        void setForegroundColor(sf::Color color);
        void setBackgroundColor(sf::Color color);

    private:
        virtual void draw(sf::RenderWindow &windowRef) override;
        virtual void locationUpdated(const sf::Vector2f &newLocation);
        virtual void rotationUpdated(float newRotation);
        void centerText();

        shared<sf::Font> m_textFont;
        sf::Text m_text;

        sf::RectangleShape m_barBack;
        sf::RectangleShape m_barFront;

        sf::Color m_foregroundColor;
        sf::Color m_backgroundColor;

        float m_percent;
    };
}