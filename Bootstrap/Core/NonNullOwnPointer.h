/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2018-2022, chris@deepscroll.com
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef NON_NULL_OWN_POINTER_H
#define NON_NULL_OWN_POINTER_H

#include "Assertions.h"
#include "RefCounted.h"
#include "Extras.h"
#include "Traits.h"
#include "Types.h"

#define NONNULLOWNPOINTER_SCRUB_BYTE 0xf1

namespace Core {
    
    template<typename T>
    class WeakPointer;

    ///

    template<typename T>
    class [[nodiscard]] NonNullOwnPointer {

    public:

        using ElementType = T;

        enum AdoptTag { 
            
            Adopt
        };

        ///

        NonNullOwnPointer(AdoptTag, T& ptr)
            : m_pointer(&ptr) {

            static_assert(
                requires { requires typename T::AllowOwnPointer()(); } || !requires { requires !typename T::AllowOwnPointer()(); declval<T>().ref(); declval<T>().unref(); },
                "Use NonNullRefPtr<> for RefCounted types");
        }

        NonNullOwnPointer(NonNullOwnPointer&& other)
            : m_pointer(other.leakPointer()) {

            VERIFY(m_pointer);
        }

        template<typename U>
        NonNullOwnPointer(NonNullOwnPointer<U>&& other)
            : m_pointer(other.leakPointer()) {

            VERIFY(m_pointer);
        }
        
        ~NonNullOwnPointer() {

            clear();

    #ifdef SANITIZE_PTRS

            m_pointer = (T*)(explodeByte(NONNULLOWNPOINTER_SCRUB_BYTE));

    #endif
        }

        NonNullOwnPointer(NonNullOwnPointer const&) = delete;

        template<typename U>
        NonNullOwnPointer(NonNullOwnPointer<U> const&) = delete;

        NonNullOwnPointer& operator=(NonNullOwnPointer const&) = delete;

        template<typename U>
        NonNullOwnPointer& operator=(NonNullOwnPointer<U> const&) = delete;

        template<typename U>
        NonNullOwnPointer(RefPointer<U> const&) = delete;

        template<typename U>
        NonNullOwnPointer(NonNullRefPointer<U> const&) = delete;

        template<typename U>
        NonNullOwnPointer(WeakPointer<U> const&) = delete;
        
        template<typename U>
        NonNullOwnPointer& operator=(RefPointer<U> const&) = delete;
        
        template<typename U>
        NonNullOwnPointer& operator=(NonNullRefPointer<U> const&) = delete;
        
        template<typename U>
        NonNullOwnPointer& operator=(WeakPointer<U> const&) = delete;

        NonNullOwnPointer& operator=(NonNullOwnPointer&& other) {

            NonNullOwnPointer ptr(move(other));
            swap(ptr);
            return *this;
        }

        template<typename U>
        NonNullOwnPointer& operator=(NonNullOwnPointer<U>&& other) {

            NonNullOwnPointer ptr(move(other));

            swap(ptr);

            return *this;
        }

        [[nodiscard]] T* leakPointer() {

            return exchange(m_pointer, nullptr);
        }

        ALWAYS_INLINE RETURNS_NONNULL T* pointer() {

            VERIFY(m_pointer);

            return m_pointer;
        }

        ALWAYS_INLINE RETURNS_NONNULL const T* pointer() const {

            VERIFY(m_pointer);

            return m_pointer;
        }

        ALWAYS_INLINE RETURNS_NONNULL T* operator->() { return pointer(); }
        ALWAYS_INLINE RETURNS_NONNULL const T* operator->() const { return pointer(); }

        ALWAYS_INLINE T& operator*() { return *pointer(); }
        ALWAYS_INLINE const T& operator*() const { return *pointer(); }

        ALWAYS_INLINE RETURNS_NONNULL operator const T*() const { return pointer(); }
        ALWAYS_INLINE RETURNS_NONNULL operator T*() { return pointer(); }

        operator bool() const = delete;
        bool operator!() const = delete;

        void swap(NonNullOwnPointer& other) {

            ::swap(m_pointer, other.m_pointer);
        }

        template<typename U>
        void swap(NonNullOwnPointer<U>& other) {

            ::swap(m_pointer, other.m_pointer);
        }

        template<typename U>
        NonNullOwnPointer<U> releaseNonNull() {

            VERIFY(m_pointer);

            return NonNullOwnPointer<U>(NonNullOwnPointer<U>::Adopt, static_cast<U&>(*leakPointer()));
        }

    private:

        void clear() {

            if (!m_pointer) {

                return;
            }

            delete m_pointer;

            m_pointer = nullptr;
        }

        T* m_pointer = nullptr;
    };

    ///

    template<typename T>
    inline NonNullOwnPointer<T> adoptOwn(T& object) {

        return NonNullOwnPointer<T>(NonNullOwnPointer<T>::Adopt, object);
    }

    template<class T, class... Args>
    requires(IsConstructible<T, Args...>) inline NonNullOwnPointer<T> make(Args&&... args) {

        return NonNullOwnPointer<T>(NonNullOwnPointer<T>::Adopt, *new T(forward<Args>(args)...));
    }

    // FIXME: Remove once P0960R3 is available in Clang.

    template<class T, class... Args>
    inline NonNullOwnPointer<T> make(Args&&... args) {

        return NonNullOwnPointer<T>(NonNullOwnPointer<T>::Adopt, *new T { forward<Args>(args)... });
    }

    ///

    template<typename T>
    struct Traits<NonNullOwnPointer<T>> : public GenericTraits<NonNullOwnPointer<T>> {

        using PeekType = T*;

        using ConstPeekType = const T*;

        static unsigned hash(NonNullOwnPointer<T> const& p) { return pointerHash((FlatPointer)p.pointer()); }

        static bool equals(NonNullOwnPointer<T> const& a, NonNullOwnPointer<T> const& b) { return a.pointer() == b.pointer(); }
    };

    template<typename T, typename U>
    inline void swap(NonNullOwnPointer<T>& a, NonNullOwnPointer<U>& b) {

        a.swap(b);
    }

    // template<typename T>
    // struct Formatter<NonNullOwnPointer<T>> : Formatter<const T*> {

    //     ErrorOr<void> format(FormatBuilder& builder, NonNullOwnPointer<T> const& value) {

    //         return Formatter<const T*>::format(builder, value.pointer());
    //     }
    // };
}

using Core::adoptOwn;
using Core::make;
using Core::NonNullOwnPointer;

#endif