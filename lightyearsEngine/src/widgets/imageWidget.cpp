#include "widgets/imageWidget.hpp"
#include "framework/assetmanager.hpp"

ly::ImageWidget::ImageWidget(const std::string & imagePath)
    :m_texture{AssetManager::get().loadTexture(imagePath)},
    m_sprite{*(m_texture.get())}
{
}

void ly::ImageWidget::setImage(const shared<sf::Texture> newTexture)
{
    if (newTexture)
    {
        m_texture = newTexture;
        m_sprite.setTexture(*(m_texture.get()));
    }
}

sf::FloatRect ly::ImageWidget::getBound() const
{
    return m_sprite.getGlobalBounds();
}

void ly::ImageWidget::draw(sf::RenderWindow & windowRef)
{
    windowRef.draw(m_sprite);
}

void ly::ImageWidget::locationUpdated(const sf::Vector2f & newLocation)
{
    m_sprite.setPosition(newLocation);
}

void ly::ImageWidget::rotationUpdated(float newRotation)
{
    m_sprite.setRotation(newRotation);
}
