#include "widgets/valueGuage.hpp"
#include "framework/assetmanager.hpp"

ly::ValueGuage::ValueGuage(const sf::Vector2f &size, float initialPercent, const sf::Color foregroundColor, const sf::Color backgroundColor)
    : m_textFont{AssetManager::get().loadFont("Bonus/kenvector_future.ttf")},
      m_text{"", *(m_textFont.get()), 18},
      m_barBack{size},
      m_barFront{size},
      m_foregroundColor{foregroundColor},
      m_backgroundColor{backgroundColor},
      m_percent{initialPercent}
{
    setForegroundColor(m_foregroundColor);
    setBackgroundColor(m_backgroundColor);
    setTextSize(18);
}

void ly::ValueGuage::setForegroundColor(sf::Color color)
{
    m_barFront.setFillColor(color);
}

void ly::ValueGuage::setBackgroundColor(sf::Color color)
{
    m_barBack.setFillColor(color);
}

void ly::ValueGuage::updateValue(float value, float maxValue)
{
    if (maxValue == 0)
        return;

    m_percent = value / maxValue;
    std::string displayStr = std::to_string((int)value) + "/" + std::to_string((int)maxValue);
    m_text.setString(displayStr);
    centerText();

    sf::Vector2f barSize = m_barBack.getSize();
    m_barFront.setSize({barSize.x * m_percent, barSize.y});
}

sf::FloatRect ly::ValueGuage::getBound() const
{
    return m_barBack.getGlobalBounds();
}

void ly::ValueGuage::setTextSize(unsigned int characterSize)
{
    m_text.setCharacterSize(characterSize);
}
void ly::ValueGuage::draw(sf::RenderWindow &windowRef)
{
    windowRef.draw(m_barBack);
    windowRef.draw(m_barFront);
    windowRef.draw(m_text);
}

void ly::ValueGuage::locationUpdated(const sf::Vector2f &newLocation)
{
    m_barBack.setPosition(newLocation);
    m_barFront.setPosition(newLocation);
    centerText();
}

void ly::ValueGuage::rotationUpdated(float newRotation)
{
    m_text.setRotation(newRotation);
    m_barBack.setRotation(newRotation);
    m_barFront.setRotation(newRotation);
}

void ly::ValueGuage::centerText()
{
    sf::Vector2f widgetCenter = getCenter();
    sf::FloatRect textBound = m_text.getGlobalBounds();
    m_text.setPosition(widgetCenter - sf::Vector2f{textBound.width / 2, textBound.height});
}
