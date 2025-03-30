#include "widgets/textWidget.hpp"
#include "framework/assetmanager.hpp"

ly::TextWidget::TextWidget(const std::string & textStr, const std::string & fontPath, unsigned int characterSize)
    : m_font{AssetManager::get().loadFont(fontPath)},
    m_text{textStr,*(m_font.get()),characterSize}
{
}

void ly::TextWidget::setString(const std::string & newStr)
{
    m_text.setString(newStr);
}

void ly::TextWidget::setCharacterSize(unsigned int newSize)
{
    m_text.setCharacterSize(newSize);
}
void ly::TextWidget::draw(sf::RenderWindow & windowRef)
{
    windowRef.draw(m_text);
}

void ly::TextWidget::locationUpdated(const sf::Vector2f & newLocation)
{
    m_text.setPosition(newLocation);
}

void ly::TextWidget::rotationUpdated(float newRotation)
{
    m_text.setRotation(newRotation);
}

sf::FloatRect ly::TextWidget::getBound() const
{
    return m_text.getGlobalBounds();
}