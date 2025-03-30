#include "widgets/widget.hpp"

ly::Widget::Widget()
    : m_visibility{true},
      m_transform{}
{
}

void ly::Widget::nativeDraw(sf::RenderWindow &windowRef)
{
    if (!isVisible())
        return;

    draw(windowRef);
}

bool ly::Widget::handleEvent(const sf::Event &event)
{
    return false;
}

void ly::Widget::setLocation(const sf::Vector2f &newLocation)
{
    m_transform.setPosition(newLocation);
    locationUpdated(newLocation);
}

void ly::Widget::setRotation(float rotation)
{
    m_transform.setRotation(rotation);
    rotationUpdated(rotation);
}

void ly::Widget::setVisibility(bool newVisibility)
{
    m_visibility = newVisibility;
}

void ly::Widget::draw(sf::RenderWindow &windowRef)
{
}

void ly::Widget::locationUpdated(const sf::Vector2f &newLocation)
{
}

void ly::Widget::rotationUpdated(float newRotation)
{
}

sf::Vector2f ly::Widget::getCenter() const
{
    sf::FloatRect bound = getBound();
    return sf::Vector2f{bound.left + bound.width/2, bound.top + bound.height/2};
}