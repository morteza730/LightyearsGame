#pragma once

#include <memory>
#include "framework/core.hpp"
#include "framework/delegate.hpp"

namespace ly
{
    class Object : public std::enable_shared_from_this<Object>
    {
    public:
        Object();
        virtual ~Object();
        bool isPendingDistroyed() { return m_isPendingDistroyed; }
        virtual void destroy();
        weak<Object> getWeakRef();
        weak<const Object> getWeakRef() const;
        const unsigned int getUniqueID() { return m_uniqueID; }
        Delegate<Object *> onDestroy;

    private:
        bool m_isPendingDistroyed;
        unsigned int m_uniqueID;

        static unsigned int getNextAvailableID();
        static unsigned int uniqueIDCounter;
    };

}