#pragma once

namespace ly{
    class Actor;
    class Shooter{
        public:
            void shoot();
            virtual bool canShoot() const {return true;}
            virtual bool isOnCoolDown() const {return false;}
            Actor* getOwner() const {return m_owner;}
        protected:
            Shooter(Actor *owner);

        private:
            Actor *m_owner;
            virtual void shootImp()=0;
    };
}