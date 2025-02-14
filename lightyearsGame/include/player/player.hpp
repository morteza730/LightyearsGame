#pragma once

#include <framework/object.hpp>
#include <framework/delegate.hpp>

namespace ly
{
    class World;
    class PlayerSpaceship;
    class Player: public Object
    {
        public:
            Player();
            weak<PlayerSpaceship> spawnSpaceShip(World *world);
            const weak<PlayerSpaceship> getCurrentSpaceship() const {return m_currentSpaceship;}
            
            int getLifeCount() const {return m_lifeCount;}
            void addLifeCount(unsigned int amt);

            int getScore() const {return m_score;}
            void addScore(unsigned int amt);
 
            Delegate<int> onLifeCountChanged;
            Delegate<int> onScoreChanged;
            Delegate<> onLifeExhausted;

        private:
            unsigned int m_lifeCount;
            unsigned int m_score;
            weak<PlayerSpaceship> m_currentSpaceship;
    };
}