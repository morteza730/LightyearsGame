#pragma once

#include <SFML/Graphics.hpp>
#include "object.hpp"
#include "framework/core.hpp"

class b2Body;

namespace ly{
    class World;
    class Actor:public Object
    {
        public:
            Actor(World *world,const std::string &texture_path="");
            virtual ~Actor();
            void beginPlayInternal();
            void tickInternal(float deltaTime);
            void setTexture(const std::string &texture_path);
            void render(sf::RenderWindow &window);

            void setActorLocation(const sf::Vector2f &location);
            void setActorRotation(float rotation);
            void addActorLocationOffset(const sf::Vector2f &offset);
            void addActorRotationOffset(float offset);
            sf::Vector2f getActorLocation() const;
            float getActorRotaion() const;
            sf::Vector2f getActorForwardDirection();
            sf::Vector2f getActorRightDirection();
            sf::Vector2u getWindowSize() const;

            const World* getWorld() const {return owningWorld;}
            World* getWorld() {return owningWorld;}

            bool isActorOutOfWindowsBounds() const;
            sf::FloatRect getActorGlobalBounds() const;
            void setEnablePhysics(bool enable);

            virtual void applyDamage(float amt);
            virtual void onActorBeginOverlap(Actor* other);
            virtual void onActorEndOverlap(Actor* other);
            virtual void distroy() override;

            uint8 getTeamID() const {return m_teamID;}
            void setTeamID(uint8 teamID){m_teamID = teamID;}
            static uint8 getNeturalTeamID() {return neturalTeamID;}
            bool isOtherHostile(Actor* other) const;

            const sf::Sprite& getSprite() const {return m_sprite;}
            sf::Sprite& getSprite(){return m_sprite;}

        protected:
            virtual void beginPlay();
            virtual void tick(float deltaTime);

        private:
            World *owningWorld;
            bool m_beginPlay;
            sf::Sprite m_sprite;
            shared<sf::Texture> m_texture;
            b2Body *m_physicsBody;
            bool m_physicsEnable;
            
            void centerPivot();
            void initializePhysics();
            void uninitializePhysics();
            void updatePhysicsBodyTransform();

            uint8 m_teamID;

            const static uint8 neturalTeamID = 255;
    };
}