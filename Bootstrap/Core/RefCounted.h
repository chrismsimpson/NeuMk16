#ifndef REF_COUNTED_H
#define REF_COUNTED_H

#include "Assertions.h"
#include "Platform.h"
#include "Checked.h"
#include "NonCopyable.h"
#include "Extras.h"

namespace Core {

    class RefCountedBase {

        MAKE_NONCOPYABLE(RefCountedBase);
        
        MAKE_NONMOVABLE(RefCountedBase);

    public:

        using RefCountType = unsigned int;
        
        using AllowOwnPointer = FalseType;

        ///

        ALWAYS_INLINE void ref() const {

            VERIFY(m_refCount > 0);

            VERIFY(!Checked<RefCountType>::additionWouldOverflow(m_refCount, 1));
            
            ++m_refCount;
        }

        ///

        [[nodiscard]] bool tryRef() const {

            if (m_refCount == 0) {

                return false;
            }

            ref();

            return true;
        }

        ///

        [[nodiscard]] RefCountType refCount() const { return m_refCount; }
    
    protected:

        RefCountedBase() = default;

        ~RefCountedBase() { 
            
            VERIFY(!m_refCount);
        }

        ///

        ALWAYS_INLINE RefCountType derefBase() const {

            VERIFY(m_refCount);

            return --m_refCount;
        }

        ///

        RefCountType mutable m_refCount { 1 };
    };

    ///

    template<typename T>
    class RefCounted: public RefCountedBase {

    public:

        bool unref() const {

            auto* that = const_cast<T*>(static_cast<T const*>(this));

            auto newRefCount = derefBase();

            if (newRefCount == 0) {

                if constexpr (requires { that->will_be_destroyed(); }) {

                    that->will_be_destroyed();
                }

                delete static_cast<const T*>(this);

                return true;
            }

            return false;
        }
    };
}

using Core::RefCounted;
using Core::RefCountedBase;

#endif