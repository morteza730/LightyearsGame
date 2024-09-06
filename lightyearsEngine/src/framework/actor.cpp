#include "framework/actor.hpp"
#include "framework/core.hpp"

ly::Actor::Actor(World *world):
    owningWorld{world},
    m_beginPlay{false}
{}

ly::Actor::~Actor()
{}

void ly::Actor::beginPlayInternal()
{
    if (!m_beginPlay){
        m_beginPlay = true;
        beginPlay();
    }
}

void ly::Actor::tick(float deltaTime)
{
    LOG("actor working at framerate: %f",1.f/deltaTime);
}

void ly::Actor::beginPlay()
{
    LOG("begin play");
}
