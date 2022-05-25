/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2022, chris@deepscroll.com
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef OWN_POINTER_H
#define OWN_POINTER_H

#include "RefCounted.h"

namespace Core {

    template<typename T>
    class [[nodiscard]] OwnPointer {

    public:

        OwnPointer() = default;

        OwnPointer(decltype(nullptr))
            : m_pointer(nullptr) { }

        OwnPointer(OwnPointer&& other)
            : m_pointer(other.leakPointer()) { }

        // template<typename U>
        // OwnPtr(NonnullOwnPtr<U>&& other)
        //     : m_ptr(other.leak_ptr()) { }

    //     template<typename U>
    //     OwnPtr(OwnPtr<U>&& other)
    //         : m_ptr(other.leak_ptr()) { }

    //     ~OwnPtr() {

    //         clear();

    // #ifdef SANITIZE_PTRS

    //         m_ptr = (T*)(explode_byte(OWNPTR_SCRUB_BYTE));

    // #endif
    //     }


        [[nodiscard]] T* leakPointer() {

            T* leakedPointer = m_pointer;
            m_pointer = nullptr;
            return leakedPointer;
        }


    private:
        T* m_pointer = nullptr;
    };
    
}


#endif