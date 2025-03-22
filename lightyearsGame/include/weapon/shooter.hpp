#pragma once

namespace ly
{
    class Actor;
    class Shooter
    {
    public:
        void shoot();
        virtual bool canShoot() const { return true; }
        virtual bool isOnCoolDown() const { return false; }
        Actor *getOwner() const { return m_owner; }
        int getCurrentLevel() const { return m_currentLevel; }
        int getMaxLevel() const { return m_maxLevel; }
        virtual void increaseLevel(int amt = 0);
        virtual void setCurrentLevel(int level);
        bool isMaxLevel() const { return m_currentLevel == m_maxLevel; }

    protected:
        Shooter(Actor *owner);

    private:
        virtual void shootImp() = 0;
        Actor *m_owner;
        int m_currentLevel;
        int m_maxLevel;
    };
}