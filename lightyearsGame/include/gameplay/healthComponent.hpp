#pragma once

#include <framework/delegate.hpp>

namespace ly{
    class HealthComponent{
        public:
            HealthComponent(float health,float maxHealth);
            void changeHealth(float amt);
            float getHealth(){return m_health;}
            float getMaxHealth(){return m_maxHealth;}

            Delegate<float,float,float> onHealthChanged;
            Delegate<float,float,float> onTakenDamage;
            Delegate<> onHealthEmpty;

        private:
            void takenDamage(float amt);
            void healthEmpty();
            // void healthRegen(float amt);
            float m_health;
            float m_maxHealth;
    };
}

