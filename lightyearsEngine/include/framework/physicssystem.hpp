#pragma once

#include "framework/core.hpp"
#include <box2d/b2_world.h>

#include <SFML/Graphics.hpp>

namespace ly
{
    class Actor;
    class PhysicsContactListener : public b2ContactListener
    {
        virtual void BeginContact(b2Contact *contact) override;
        virtual void EndContact(b2Contact *contact) override;
    };

    class PhysicsSystem
    {
    public:
        static PhysicsSystem &get();
        void step(float deltaTime);
        b2Body *addListener(Actor *listener);
        void removeListener(b2Body *bodyToRemove);
        float getPhysicsScale() { return m_physicsScale; }
        b2World* getWorld();

    protected:
        PhysicsSystem();

    private:
        static unique<PhysicsSystem> physics_system;
        b2World m_physicsWorld;
        float m_physicsScale;
        float m_velocityIteration;
        float m_positionIteration;
        PhysicsContactListener m_contactListener;
    };
}