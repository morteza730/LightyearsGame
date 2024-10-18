#pragma once

#include "shooter.hpp"
#include <sfml/System.hpp>

namespace ly{
    class BulletShooter: public Shooter{
        public:
            BulletShooter(Actor* owner,float coolDownTime=1.f);
            virtual bool isOnCoolDown() const override;

        private:
            virtual void shootImp() override;
            sf::Clock m_coolDownTimer;
            float m_coolDownTime;
    };
}