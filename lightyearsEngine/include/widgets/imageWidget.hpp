#pragma once

#include "widgets/widget.hpp"
#include <sfml/Graphics.hpp>

namespace ly
{
    class ImageWidget : public Widget
    {
    public:
        ImageWidget(const std::string &imagePath);
        void setImage(const shared<sf::Texture> newTexture);
        virtual sf::FloatRect getBound() const override;

    private:
        virtual void draw(sf::RenderWindow &windowRef) override;
        virtual void locationUpdated(const sf::Vector2f& newLocation) override;
        virtual void rotationUpdated(float newRotation) override;
        shared<sf::Texture> m_texture;
        sf::Sprite m_sprite;
    };
}