#include "framework/object.hpp"
#include "framework/core.hpp"

ly::Object::Object():
    m_isPendingDistroyed{false}
{}

ly::Object::~Object()
{
    LOG("object distroyed");
}

void ly::Object::distroy()
{
    m_isPendingDistroyed = true;
}