/*
 * Copyright (c) 2018-2022, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2022, chris@deepscroll.com
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef TRAITS_H
#define TRAITS_H

#include "Concepts.h"
#include "HashFunctions.h"

namespace Core {

    template<typename T>
    struct GenericTraits {

        using PeekType = T&;

        using ConstPeekType = T const&;

        static constexpr bool isTrivial() { return false; }

        static constexpr bool equals(const T& a, const T& b) { return a == b; }

        template<Concepts::HashCompatible<T> U>
        static bool equals(U const& a, T const& b) { return a == b; }
    };

    ///

    template<typename T>
    struct Traits : public GenericTraits<T> { };

    template<typename T>
    requires(IsIntegral<T>) struct Traits<T> : public GenericTraits<T> {

        static constexpr bool isTrivial() { return true; }

        static constexpr unsigned hash(T value) {

            if constexpr (sizeof(T) < 8) {

                return intHash(value);
            }
            else {

                return u64Hash(value);
            }
        }
    };
    
}

#endif