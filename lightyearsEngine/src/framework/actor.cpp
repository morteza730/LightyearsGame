#include <box2d/b2_body.h>

#include "framework/actor.hpp"
#include "framework/core.hpp"
#include "framework/assetmanager.hpp"
#include "framework/mathutility.hpp"
#include "framework/world.hpp"
#include "framework/physicssystem.hpp"

ly::Actor::Actor(World *world,const std::string &texture_path):
    owningWorld{world},
    m_beginPlay{false},
    m_texture{nullptr},
    m_sprite{},
    m_physicsBody{nullptr},
    m_physicsEnable{false}
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
    updatePhysicsBodyTransform();
}

void ly::Actor::setActorRotation(float rotation)
{
    m_sprite.setRotation(rotation);
    updatePhysicsBodyTransform();
}

void ly::Actor::addActorLocationOffset(const sf::Vector2f &offset)
{
    setActorLocation(getActorLocation()+offset);
}

void ly::Actor::addActorRotationOffset(float offset)
{
   setActorRotation(getActorRotaion()+offset);
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
    return rotation2vector(getActorRotaion()-90.f);
}
sf::Vector2f ly::Actor::getActorRightDirection()
{
    return rotation2vector(getActorRotaion());
}

sf::Vector2u ly::Actor::getWindowSize() const
{
    return owningWorld->getWindowSize();
}

bool ly::Actor::isActorOutOfWindowsBounds() const
{
    const float windows_width = getWindowSize().x;
    const float windows_height = getWindowSize().y;
    const float width = getActorGlobalBounds().width;
    const float height = getActorGlobalBounds().height;
    const sf::Vector2f current_location = getActorLocation();
    if (current_location.x<-width || current_location.x>windows_width + width){
        return true;
    }else if (current_location.y<-height || current_location.y>windows_height + height){
        return true;
    }
    return false;
}

sf::FloatRect ly::Actor::getActorGlobalBounds() const
{
    return m_sprite.getGlobalBounds();
}

void ly::Actor::setEnablePhysics(bool enable)
{
    m_physicsEnable = enable;
    if (m_physicsEnable){
        initializePhysics();
    }else{
        uninitializePhysics();
    }
}

void ly::Actor::initializePhysics()
{
    if (!m_physicsBody){
        m_physicsBody = PhysicsSystem::get().addListener(this);
    }
}

void ly::Actor::uninitializePhysics()
{
    if (m_physicsBody){
        PhysicsSystem::get().removeListener(m_physicsBody);
    }
}

void ly::Actor::updatePhysicsBodyTransform()
{
    if (m_physicsBody){
        float physicsSclale = PhysicsSystem::get().getPhysicsScale();
        b2Vec2 pos{getActorLocation().x*physicsSclale,getActorLocation().y*physicsSclale};
        float rotation = degree2raduis(getActorRotaion());

        m_physicsBody->SetTransform(pos,rotation);
    }
}

void ly::Actor::beginPlay()
{
    // LOG("begin play");
}

void ly::Actor::tickInternal(float deltaTime)
{
    if (isPendingDistroyed()){
        return;
    }
    tick(deltaTime);
}
