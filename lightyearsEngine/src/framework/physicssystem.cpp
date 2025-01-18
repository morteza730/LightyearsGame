#include <box2d/b2_body.h>
#include <box2d/b2_contact.h>
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
        physics_system = std::move(unique<PhysicsSystem>{new PhysicsSystem()});
    }
    return *physics_system;
}

ly::PhysicsSystem::PhysicsSystem() : m_physicsWorld{b2Vec2{0.f, 0.f}},
                                     m_physicsScale{0.01f},
                                     m_velocityIteration{8.f},
                                     m_positionIteration{3.f},
                                     m_contactListener{},
                                     m_pendingRemoveListeners{}
{
    m_physicsWorld.SetContactListener(&m_contactListener);
    m_physicsWorld.SetAllowSleeping(false);
}

void ly::PhysicsSystem::step(float deltaTime)
{
    processPendingRemoveListeners();
    m_physicsWorld.Step(deltaTime, m_velocityIteration, m_positionIteration);
}

void ly::PhysicsSystem::processPendingRemoveListeners()
{
    for (auto listener: m_pendingRemoveListeners)
    {
        m_physicsWorld.DestroyBody(listener);
    }
    m_pendingRemoveListeners.clear();
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
    // fixtureDef.filter.categoryBits = 1;
    // fixtureDef.filter.maskBits = 1;
    fixtureDef.isSensor = true;
    body->CreateFixture(&fixtureDef);

    return body;
}

void ly::PhysicsSystem::removeListener(b2Body *bodyToRemove)
{
    m_pendingRemoveListeners.insert(bodyToRemove);
}

b2World *ly::PhysicsSystem::getWorld()
{

    return &m_physicsWorld;
}

void ly::PhysicsSystem::cleanup()
{
     physics_system = std::move(unique<PhysicsSystem>{new PhysicsSystem()});
}

void ly::PhysicsContactListener::BeginContact(b2Contact *contact)
{
    Actor *actorA = reinterpret_cast<Actor *>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    Actor *actorB = reinterpret_cast<Actor *>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    if (actorA && !actorA->isPendingDistroyed())
    {
        actorA->onActorBeginOverlap(actorB);
    }

    if (actorB && !actorB->isPendingDistroyed())
    {
        actorB->onActorBeginOverlap(actorA);
    }
}

void ly::PhysicsContactListener::EndContact(b2Contact *contact)
{
    Actor* actorA = nullptr;
    Actor* actorB = nullptr;

    if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
    {
        actorA = reinterpret_cast<Actor *>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    }

    if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
    {
        actorB = reinterpret_cast<Actor *>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
    }

    if (actorA && !actorA->isPendingDistroyed())
    {
        actorA->onActorEndOverlap(actorB);
    }

    if (actorB && !actorB->isPendingDistroyed())
    {
        actorB->onActorEndOverlap(actorA);
    }
}
