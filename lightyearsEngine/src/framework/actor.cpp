#include "framework/actor.hpp"
#include "framework/core.hpp"
#include "framework/assetmanager.hpp"
#include "framework/mathutility.hpp"

ly::Actor::Actor(World *world,const std::string &texture_path):
    owningWorld{world},
    m_beginPlay{false},
    m_texture{nullptr},
    m_sprite{}
{
    setTexture(texture_path);
}

ly::Actor::~Actor()
{}

void ly::Actor::beginPlayInternal()
{
    if (!m_beginPlay){
        m_beginPlay = true;
        beginPlay();
    }
}

void ly::Actor::tick(float deltaTime)
{
    // LOG("actor working at framerate: %f",1.f/deltaTime);
}

void ly::Actor::centerPivot()
{
    sf::Rect<float> bound = m_sprite.getGlobalBounds();
    m_sprite.setOrigin(bound.width/2.f,bound.height/2.f);
}
void ly::Actor::setTexture(const std::string &texture_path)
{
    m_texture = AssetManager::get().loadTexture(texture_path);
    if (!m_texture) return;
    m_sprite.setTexture(*m_texture);
    int texture_width = m_texture->getSize().x;
    int texture_height = m_texture->getSize().y;
    m_sprite.setTextureRect(sf::IntRect{sf::Vector2i{},sf::Vector2i{texture_width,texture_height}});
    centerPivot();
}

void ly::Actor::render(sf::RenderWindow &window)
{
    if (isPendingDistroyed()){
        return;
    }
    window.draw(m_sprite);
}

void ly::Actor::setActorLocation(const sf::Vector2f& location)
{
    m_sprite.setPosition(location);
}

void ly::Actor::setActorRotation(float rotation)
{
    m_sprite.setRotation(rotation);
}

void ly::Actor::addActorLocationOffset(const sf::Vector2f &offset)
{
    m_sprite.setPosition(getActorLocation()+offset);
}

void ly::Actor::addActorRotationOffset(float offset)
{
    m_sprite.setRotation(getActorRotaion()+offset);
}

sf::Vector2f ly::Actor::getActorLocation() const
{
    return m_sprite.getPosition();
}

float ly::Actor::getActorRotaion() const
{
    return m_sprite.getRotation();
}

sf::Vector2f ly::Actor::getActorForwardDirection()
{
    return rotation2vector(getActorRotaion());
}
sf::Vector2f ly::Actor::getActorRightDirection()
{
    return rotation2vector(getActorRotaion()+90.f);
}
void ly::Actor::beginPlay()
{
    LOG("begin play");
}

void ly::Actor::tickInternal(float deltaTime)
{
    if (isPendingDistroyed()){
        return;
    }
    tick(deltaTime);
}
