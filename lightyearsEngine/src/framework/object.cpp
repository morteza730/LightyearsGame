#include "framework/object.hpp"
#include "framework/core.hpp"

ly::Object::Object():
    m_isPendingDistroyed{false}
{}

ly::Object::~Object()
{
    LOG("object destroyed");
}

void ly::Object::destroy()
{
    onDistroy.broadCast(this);
    m_isPendingDistroyed = true;
}

ly::weak<ly::Object> ly::Object::getWeakRef()
{
    return weak_from_this();
}

ly::weak<const ly::Object> ly::Object::getWeakRef() const
{
    return weak_from_this();
}
