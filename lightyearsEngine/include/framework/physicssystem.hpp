#pragma once

#include "framework/core.hpp"
#include <box2d/b2_world.h>

namespace ly{
    class Actor;
    class PhysicsSystem{
        public:
            static PhysicsSystem& get();
            void step(float deltaTime);
            b2Body* addListener(Actor* listener);
            void removeListener(b2Body* bodyToRemove);
            float getPhysicsScale(){return m_physicsScale;}

        protected:
            PhysicsSystem();
            PhysicsSystem(PhysicsSystem &instance);
            PhysicsSystem(PhysicsSystem &&instance);

        private:
            static unique<PhysicsSystem> physics_system;
            b2World m_physicsWorld;
            float m_physicsScale;
            float m_velocityIteration;
            float m_positionIteration;
    };
}