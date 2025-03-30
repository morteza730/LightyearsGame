#pragma once

#include <sfml/Graphics.hpp>
#include "framework/object.hpp"

namespace ly
{
    class Widget : public Object
    {
    public:
        void nativeDraw(sf::RenderWindow &windowRef);
        virtual bool handleEvent(const sf::Event &event);
        void setLocation(const sf::Vector2f &newLocation);
        void setRotation(float rotation);
        sf::Vector2f getLocation() const { return m_transform.getPosition(); }
        float getRotation() const { return m_transform.getRotation(); }
        void setVisibility(bool newVisibility);
        bool isVisible() const { return m_visibility; }
        virtual sf::FloatRect getBound() const = 0;
        sf::Vector2f getCenter() const;

    protected:
        Widget();

    private:
        virtual void draw(sf::RenderWindow &windowRef);
        virtual void locationUpdated(const sf::Vector2f& newLocation);
        virtual void rotationUpdated(float newRotation);
        sf::Transformable m_transform;
        bool m_visibility;
    };
}