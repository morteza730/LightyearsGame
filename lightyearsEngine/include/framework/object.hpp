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
        Delegate<Object*> onDistroy;

    private:
        bool m_isPendingDistroyed;
    };

}