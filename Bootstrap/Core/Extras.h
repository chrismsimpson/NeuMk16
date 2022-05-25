/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2022, chris@deepscroll.com
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef EXTRAS_H
#define EXTRAS_H

#include "Detail.h"
#include "Assertions.h"

template<typename T, typename U>
constexpr auto roundUpToPowerOfTwo(T value, U power_of_two) requires(IsIntegral<T>&& IsIntegral<U>) {

    return ((value - 1) & ~(power_of_two - 1)) + power_of_two;
}

///

template<typename T>
constexpr bool isPowerOfTwo(T value) requires(IsIntegral<T>) {

    return value && !((value) & (value - 1));
}

///

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

namespace Core::Detail {
    
    template<typename T>
    struct _RawPointer {

        using Type = T*;
    };
}

///

namespace Core {

    template<typename T, typename SizeType = decltype(sizeof(T)), SizeType N>
    constexpr SizeType arraySize(T (&)[N]) {

        return N;
    }

    ///

    template<typename T>
    constexpr T min(const T& a, IdentityType<T> const& b) {

        return b < a ? b : a;
    }

    ///

    template<typename T>
    constexpr T max(const T& a, IdentityType<T> const& b) {

        return a < b ? b : a;
    }

    ///

    template<typename T>
    constexpr T clamp(const T& value, IdentityType<T> const& min, IdentityType<T> const& max) {

        VERIFY(max >= min);

        if (value > max) {

            return max;
        }
        
        if (value < min) {

            return min;
        }

        return value;
    }

    ///

    template<typename T, typename U>
    constexpr T mix(T const& v1, T const& v2, U const& interpolation) {

        return v1 + (v2 - v1) * interpolation;
    }

    ///

    template<typename T, typename U>
    constexpr T ceilDiv(T a, U b) {

        static_assert(sizeof(T) == sizeof(U));

        T result = a / b;

        if ((a % b) != 0) {

            ++result;
        }

        return result;
    }

    ///

    template<typename T, typename U>
    inline void swap(T& a, U& b) {

        if (&a == &b) {

            return;
        }

        U tmp = move((U&)a);

        a = (T &&) move(b);

        b = move(tmp);
    }

    ///

    template<typename T, typename U = T>
    constexpr T exchange(T& slot, U&& value) {

        T oldValue = move(slot);

        slot = forward<U>(value);

        return oldValue;
    }

    ///

    template<typename T>
    using RawPointer = typename Detail::_RawPointer<T>::Type;

    ///

    template<typename V>
    constexpr decltype(auto) toUnderlying(V value) requires(IsEnum<V>) {

        return static_cast<UnderlyingType<V>>(value);
    }

    ///

    constexpr bool isConstantEvaluated() {

    #if __has_builtin(__builtin_is_constant_evaluated)

        return __builtin_is_constant_evaluated();

    #else

        return false;

    #endif
    }

    ///

    // These can't be exported into the global namespace as they would clash with the C standard library.

    #define __DEFINE_GENERIC_ABS(type, zero, intrinsic) \
        constexpr type abs(type num) {                  \
                                                        \
            if (isConstantEvaluated()) {                \
                return num < (zero) ? -num : num;       \
            }                                           \
                                                        \
            return __builtin_##intrinsic(num);          \
        }

    __DEFINE_GENERIC_ABS(int, 0, abs);
    __DEFINE_GENERIC_ABS(long, 0L, labs);
    __DEFINE_GENERIC_ABS(long long, 0LL, llabs);
    __DEFINE_GENERIC_ABS(float, 0.0F, fabsf);
    __DEFINE_GENERIC_ABS(double, 0.0, fabs);
    __DEFINE_GENERIC_ABS(long double, 0.0L, fabsl);

    #undef __DEFINE_GENERIC_ABS
}

using Core::arraySize;
using Core::ceilDiv;
using Core::clamp;
using Core::exchange;
using Core::isConstantEvaluated;
using Core::max;
using Core::min;
using Core::mix;
using Core::RawPointer;
using Core::swap;
using Core::toUnderlying;

#endif