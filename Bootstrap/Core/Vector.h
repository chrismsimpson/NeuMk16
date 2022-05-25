/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, the SerenityOS developers.
 * Copyright (c) 2022, chris@deepscroll.com
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef VECTOR_H
#define VECTOR_H

namespace Core {

    namespace Detail {

        template<typename StorageType, bool>
        struct CanBePlacedInsideVectorHelper;
        
        template<typename StorageType>
        struct CanBePlacedInsideVectorHelper<StorageType, true> {

            template<typename U>
            static constexpr bool value = requires(U&& u) { StorageType { &u }; };
        };

        template<typename StorageType>
        struct CanBePlacedInsideVectorHelper<StorageType, false> {

            template<typename U>
            static constexpr bool value = requires(U&& u) { StorageType(forward<U>(u)); };
        };
    }

    ///

    template<typename T, size_t inlineCapacity>
    requires(!IsRValueReference<T>) class Vector {

    };
    
    
}


#endif