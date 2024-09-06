#pragma once

#include "object.hpp"

namespace ly{
    class World;
    class Actor:public Object
    {
        public:
            Actor(World *world);
            virtual ~Actor();
            void beginPlayInternal();
            void beginPlay();
            void tick(float deltaTime);

        private:
            World *owningWorld;
            bool m_beginPlay;
    };
}