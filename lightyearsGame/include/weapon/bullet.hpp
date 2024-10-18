#pragma once

#include <framework/actor.hpp>

namespace ly{
    class Bullet: public Actor{
        public:
            Bullet(World *world,Actor *owner,const std::string &texture_path,float damage=10.f,float speed=600.f);
            void setSpeed(float newSpeed);
            void setDamage(float newdamage);
            virtual void tick(float deltaTime) override;
            virtual void beginPlay() override;
            
        private:
            void move(float deltaTime);
            Actor *m_owner;
            float m_damage;
            float m_speed;
    };
}