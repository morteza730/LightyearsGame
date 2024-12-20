#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include "framework/physicssystem.hpp"
#include "framework/actor.hpp"
#include "framework/mathutility.hpp"

ly::unique<ly::PhysicsSystem> ly::PhysicsSystem::physics_system{nullptr};

ly::PhysicsSystem &ly::PhysicsSystem::get()
{
    if (!physics_system)
    {
        physics_system = unique<PhysicsSystem>{new PhysicsSystem()};
    }
    return *physics_system;
}

void ly::PhysicsSystem::step(float deltaTime)
{
    m_physicsWorld.Step(deltaTime, m_velocityIteration, m_positionIteration);
}

b2Body *ly::PhysicsSystem::addListener(Actor *listener)
{
    if (listener->isPendingDistroyed())
        return nullptr;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);
    bodyDef.position.Set(listener->getActorLocation().x * getPhysicsScale(), listener->getActorLocation().y * getPhysicsScale());
    bodyDef.angle = degree2raduis(listener->getActorRotaion());

    b2Body *body = m_physicsWorld.CreateBody(&bodyDef);

    b2PolygonShape shape;
    auto bound = listener->getActorGlobalBounds();
    shape.SetAsBox(bound.width / 2.f * getPhysicsScale(), bound.height / 2.f * getPhysicsScale());

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = 1;
    fixtureDef.filter.maskBits = 1;
    fixtureDef.isSensor = true;
    body->CreateFixture(&fixtureDef);

    return body;
}

void ly::PhysicsSystem::removeListener(b2Body *bodyToRemove)
{
    // TODO: implement removal of physics body.
}

b2World *ly::PhysicsSystem::getWorld()
{

    return &m_physicsWorld;
}

ly::PhysicsSystem::PhysicsSystem() : m_physicsWorld{b2Vec2{0.f, 0.f}},
                                     m_physicsScale{0.01f},
                                     m_velocityIteration{8.f},
                                     m_positionIteration{3.f},
                                     m_contactListener{}
{
    m_physicsWorld.SetContactListener(&m_contactListener);
    m_physicsWorld.SetAllowSleeping(false);
}

void ly::PhysicsContactListener::BeginContact(b2Contact *contact)
{
    LOG("Contact");
}

void ly::PhysicsContactListener::EndContact(b2Contact *contact)
{
    LOG("End Contact");
}
