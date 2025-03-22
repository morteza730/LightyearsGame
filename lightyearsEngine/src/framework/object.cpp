#include "framework/object.hpp"
#include "framework/core.hpp"

namespace ly
{
    unsigned int Object::uniqueIDCounter = 0;
}

ly::Object::Object() : m_isPendingDistroyed{false},
                       m_uniqueID{getNextAvailableID()}
{
}

ly::Object::~Object()
{
    // LOG("object destroyed");
}

void ly::Object::destroy()
{
    onDestroy.broadCast(this);
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

unsigned int ly::Object::getNextAvailableID()
{
    return uniqueIDCounter++;
}
