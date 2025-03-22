#pragma once

#include "framework/core.hpp"
#include "widgets/widget.hpp"

namespace ly
{
    class TextWidget : public Widget
    {
    public:
        TextWidget(const std::string &textStr = "",
                   const std::string &fontPath = "Bonus/kenvector_future.ttf",
                   unsigned int characterSize = 10);

        void setString(const std::string &newStr);
        void setCharacterSize(unsigned int newSize);
        virtual sf::FloatRect getBound() const override;

    private:
        virtual void draw(sf::RenderWindow &windowRef) override;
        virtual void locationUpdated(const sf::Vector2f &newLocation) override;
        virtual void rotationUpdated(float newRotation) override;
        shared<sf::Font> m_font;
        sf::Text m_text;
    };

}