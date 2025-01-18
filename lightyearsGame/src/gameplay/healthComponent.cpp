#include "gameplay/healthComponent.hpp"
#include <framework/core.hpp>


ly::HealthComponent::HealthComponent(float health, float maxHealth) : m_health{health},
                                                                      m_maxHealth{maxHealth}
{
}

void ly::HealthComponent::changeHealth(float amt)
{
    if (amt == 0)
        return;
    if (m_health == 0)
        return;

    m_health += amt;
    if (m_health < 0)
    {
        m_health = 0;
    }
    if (m_health > m_maxHealth)
    {
        m_health = m_maxHealth;
    }

    if (amt < 0)
    {
        takenDamage(-amt);
        if (m_health==0)
        {
            healthEmpty();
        }
    }
    onHealthChanged.broadCast(amt,m_health,m_maxHealth);
}

void ly::HealthComponent::takenDamage(float amt)
{
    onTakenDamage.broadCast(amt,m_health,m_maxHealth);
}

void ly::HealthComponent::healthEmpty()
{
    onHealthEmpty.broadCast();
}
