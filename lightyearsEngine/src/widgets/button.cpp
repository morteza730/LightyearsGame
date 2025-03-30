#include "widgets/button.hpp"
#include "framework/assetmanager.hpp"

ly::Button::Button(const std::string &text, const std::string &texturePath, const std::string &fontPath)
    : m_texture{AssetManager::get().loadTexture(texturePath)},
      m_sprite{*(m_texture.get())},
      m_font{AssetManager::get().loadFont(fontPath)},
      m_text{text, *(m_font.get())},
      m_buttonDefaultColor{128, 128, 128, 255},
      m_buttonHoverColor{190, 190, 190, 255},
      m_buttonDownColor{64, 64, 64, 255},
      m_isDown{false}
{
    m_sprite.setColor(m_buttonDefaultColor);
}

sf::FloatRect ly::Button::getBound() const
{
    return m_sprite.getGlobalBounds();
}

void ly::Button::setText(const std::string &text)
{
    m_text.setString(text);
    centerText();
}

void ly::Button::setCharacterSize(unsigned int size)
{
    m_text.setCharacterSize(size);
    centerText();
}

void ly::Button::draw(sf::RenderWindow &windowRef)
{
    windowRef.draw(m_sprite);
    windowRef.draw(m_text);
}

void ly::Button::locationUpdated(const sf::Vector2f &newLocation)
{
    m_sprite.setPosition(newLocation);
    centerText();
}

void ly::Button::rotationUpdated(float newRotation)
{
    m_sprite.setRotation(newRotation);
    m_text.setRotation(newRotation);
}

void ly::Button::centerText()
{
    sf::Vector2f widgetCenter = getCenter();
    sf::FloatRect textBound = m_text.getGlobalBounds();
    m_text.setPosition(widgetCenter - sf::Vector2f{textBound.width / 2, textBound.height});
}

bool ly::Button::handleEvent(const sf::Event &event)
{
    bool handled = false;
    if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (m_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && m_isDown)
            {
                onButtonClicked.broadCast();
                handled = true;
            }
        }
        buttonUp();
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        if (m_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
            buttonDown();
            handled = true;
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (m_sprite.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
            {
                mouseHover();
            }
            else
            {
                buttonUp();
            }
            handled = true;
        }
    }
    return handled || Widget::handleEvent(event);
}

void ly::Button::buttonUp()
{
    m_isDown = false;
    m_sprite.setColor(m_buttonDefaultColor);
}

void ly::Button::buttonDown()
{
    m_isDown = true;
    m_sprite.setColor(m_buttonDownColor);
}

void ly::Button::mouseHover()
{
    m_sprite.setColor(m_buttonHoverColor);
}