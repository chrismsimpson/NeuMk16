/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2022, chris@deepscroll.com
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef EXTRAS_H
#define EXTRAS_H

#include "Detail.h"

namespace std {

    template<typename T>
    constexpr T&& forward(Core::Detail::RemoveReference<T>& param) {

        return static_cast<T&&>(param);
    }

    template<typename T>
    constexpr T&& forward(Core::Detail::RemoveReference<T>&& param) noexcept {

        static_assert(!IsLValueReference<T>, "Can't forward an rvalue as an lvalue.");

        return static_cast<T&&>(param);
    }

    template<typename T>
    constexpr T&& move(T& arg) {

        return static_cast<T&&>(arg);
    }
}

using std::forward;
using std::move;

///

template<typename T, typename U = T>
constexpr T exchange(T& slot, U&& value) {

    T oldValue = move(slot);
    slot = forward<U>(value);
    return oldValue;
}

#endif