#ifndef REF_COUNTED_H
#define REF_COUNTED_H

#include "Noncopyable.h"
#include "Detail.h"
#include "RefCounted.h"
#include "Assertions.h"
#include "Platform.h"

namespace Core {

    class RefCountedBase {

        MAKE_NONCOPYABLE(RefCountedBase);
        MAKE_NONMOVABLE(RefCountedBase);

    public:

        using RefCountedType = unsigned int;
        using AllowOwnPointer = FalseType;

        ALWAYS_INLINE void ref() const {

            VERIFY(m_refCount > 0);
            
            // VERIFY!
        }
    
    protected:

        RefCountedBase() = default;

        ~RefCountedBase() { 
            
            VERIFY(!m_refCount);
        }

        ///

        RefCountedType mutable m_refCount { 1 };
    };

    ///

    template<typename T>
    class RefCounted: public RefCountedBase {

    };
}

using Core::RefCounted;
using Core::RefCountedBase;

#endif