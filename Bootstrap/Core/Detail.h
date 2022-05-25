/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Ali Mohammad Pur <mpfard@serenityos.org>
 * Copyright (c) 2021, Daniel Bertalan <dani@danielbertalan.dev>
 * Copyright (c) 2022, chris@deepscroll.com
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef DETAIL_H
#define DETAIL_H

namespace Core::Detail {

    template<class T, T v>
    struct IntegralConstant {

        static constexpr T value = v;

        using ValueType = T;
        
        using Type = IntegralConstant;

        constexpr operator ValueType() const { return value; }

        constexpr ValueType operator()() const { return value; }
    };

    using FalseType = IntegralConstant<bool, false>;
    
    using TrueType = IntegralConstant<bool, true>;

    ///

    template<class T>
    using AddConst = const T;

    template<class T>
    struct __AddConstToReferencedType {

        using Type = T;
    };

    template<class T>
    struct __AddConstToReferencedType<T&> {

        using Type = AddConst<T>&;
    };

    template<class T>
    struct __AddConstToReferencedType<T&&> {

        using Type = AddConst<T>&&;
    };

    template<class T>
    using AddConstToReferencedType = typename __AddConstToReferencedType<T>::Type;

    ///

    template<class T>
    struct __RemoveConst {

        using Type = T;
    };

    template<class T>
    struct __RemoveConst<const T> {

        using Type = T;
    };

    template<class T>
    using RemoveConst = typename __RemoveConst<T>::Type;

    ///

    template<class T>
    struct __RemoveVolatile {

        using Type = T;
    };

    template<class T>
    struct __RemoveVolatile<volatile T> {

        using Type = T;
    };

    template<typename T>
    using RemoveVolatile = typename __RemoveVolatile<T>::Type;

    template<class T>
    using RemoveConstVolatile = RemoveVolatile<RemoveConst<T>>;

    //

    template<typename...>
    using VoidType = void;

    ///

    template<class T>
    inline constexpr bool IsLValueReference = false;

    template<class T>
    inline constexpr bool IsLValueReference<T&> = true;

    ///

    template<class T>
    inline constexpr bool __IsPointerHelper = false;

    template<class T>
    inline constexpr bool __IsPointerHelper<T*> = true;

    template<class T>
    inline constexpr bool IsPointer = __IsPointerHelper<RemoveConstVolatile<T>>;

    ///

    template<class>
    inline constexpr bool IsFunction = false;

    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args...)> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args..., ...)> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args...) const> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args..., ...) const> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args...) volatile> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args..., ...) volatile> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args...) const volatile> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args..., ...) const volatile> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args...)&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args..., ...)&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args...) const&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args..., ...) const&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args...) volatile&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args..., ...) volatile&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args...) const volatile&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args..., ...) const volatile&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args...) &&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args..., ...) &&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args...) const&&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args..., ...) const&&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args...) volatile&&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args..., ...) volatile&&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args...) const volatile&&> = true;
    
    template<class Ret, class... Args>
    inline constexpr bool IsFunction<Ret(Args..., ...) const volatile&&> = true;

    ///

    template<class T>
    inline constexpr bool IsRValueReference = false;

    template<class T>
    inline constexpr bool IsRValueReference<T&&> = true;

    ///

    template<class T>
    struct __RemovePointer {

        using Type = T;
    };

    template<class T>
    struct __RemovePointer<T*> {

        using Type = T;
    };

    template<class T>
    struct __RemovePointer<T* const> {

        using Type = T;
    };

    template<class T>
    struct __RemovePointer<T* volatile> {

        using Type = T;
    };

    template<class T>
    struct __RemovePointer<T* const volatile> {

        using Type = T;
    };

    template<typename T>
    using RemovePointer = typename __RemovePointer<T>::Type;

    ///

    template<typename T, typename U>
    inline constexpr bool IsSame = false;

    template<typename T>
    inline constexpr bool IsSame<T, T> = true;

    ///

    template<bool condition, class TrueType, class FalseType>
    struct __Conditional {

        using Type = TrueType;
    };

    template<class TrueType, class FalseType>
    struct __Conditional<false, TrueType, FalseType> {

        using Type = FalseType;
    };

    template<bool condition, class TrueType, class FalseType>
    using Conditional = typename __Conditional<condition, TrueType, FalseType>::Type;

    ///

    template<typename T>
    inline constexpr bool IsNullPointer = IsSame<decltype(nullptr), RemoveConstVolatile<T>>;

    ///

    template<typename T>
    struct __RemoveReference {

        using Type = T;
    };

    template<class T>
    struct __RemoveReference<T&> {

        using Type = T;
    };

    template<class T>
    struct __RemoveReference<T&&> {

        using Type = T;
    };

    template<typename T>
    using RemoveReference = typename __RemoveReference<T>::Type;

    template<typename T>
    using RemoveConstVolatileReference = RemoveConstVolatile<RemoveReference<T>>;

    ///

    template<typename T>
    struct __MakeUnsigned {

        using Type = void;
    };

    template<>
    struct __MakeUnsigned<signed char> {

        using Type = unsigned char;
    };
    
    template<>
    struct __MakeUnsigned<short> {

        using Type = unsigned short;
    };
    
    template<>
    struct __MakeUnsigned<int> {
        using Type = unsigned int;
    };
    
    template<>
    struct __MakeUnsigned<long> {

        using Type = unsigned long;
    };
    
    template<>
    struct __MakeUnsigned<long long> {

        using Type = unsigned long long;
    };
    
    template<>
    struct __MakeUnsigned<unsigned char> {

        using Type = unsigned char;
    };
    
    template<>
    struct __MakeUnsigned<unsigned short> {

        using Type = unsigned short;
    };
    
    template<>
    struct __MakeUnsigned<unsigned int> {

        using Type = unsigned int;
    };
    
    template<>
    struct __MakeUnsigned<unsigned long> {

        using Type = unsigned long;
    };
    
    template<>
    struct __MakeUnsigned<unsigned long long> {

        using Type = unsigned long long;
    };
    
    template<>
    struct __MakeUnsigned<char> {

        using Type = unsigned char;
    };
    
    template<>
    struct __MakeUnsigned<char8_t> {

        using Type = char8_t;
    };
    
    template<>
    struct __MakeUnsigned<char16_t> {

        using Type = char16_t;
    };
    
    template<>
    struct __MakeUnsigned<char32_t> {
    
        using Type = char32_t;
    };
    
    template<>
    struct __MakeUnsigned<bool> {
    
        using Type = bool;
    };

    template<typename T>
    using MakeUnsigned = typename __MakeUnsigned<T>::Type;

    ///

    template<typename T>
    struct __MakeSigned {

        using Type = void;
    };
    
    template<>
    struct __MakeSigned<signed char> {

        using Type = signed char;
    };
    
    template<>
    struct __MakeSigned<short> {

        using Type = short;
    };
    
    template<>
    struct __MakeSigned<int> {

        using Type = int;
    };
    
    template<>
    struct __MakeSigned<long> {

        using Type = long;
    };
    
    template<>
    struct __MakeSigned<long long> {

        using Type = long long;
    };
    
    template<>
    struct __MakeSigned<unsigned char> {

        using Type = char;
    };
    
    template<>
    struct __MakeSigned<unsigned short> {

        using Type = short;
    };
    
    template<>
    struct __MakeSigned<unsigned int> {

        using Type = int;
    };
    
    template<>
    struct __MakeSigned<unsigned long> {

        using Type = long;
    };
    
    template<>
    struct __MakeSigned<unsigned long long> {

        using Type = long long;
    };

    template<>
    struct __MakeSigned<char> {

        using Type = char;
    };

    template<typename T>
    using MakeSigned = typename __MakeSigned<T>::Type;

    ///

    template<typename T>
    auto declval() -> T;

    ///

    template<typename...>
    struct __CommonType;

    template<typename T>
    struct __CommonType<T> {

        using Type = T;
    };

    template<typename T1, typename T2>
    struct __CommonType<T1, T2> {

        using Type = decltype(true ? declval<T1>() : declval<T2>());
    };

    template<typename T1, typename T2, typename... Ts>
    struct __CommonType<T1, T2, Ts...> {

        using Type = typename __CommonType<typename __CommonType<T1, T2>::Type, Ts...>::Type;
    };

    template<typename... Ts>
    using CommonType = typename __CommonType<Ts...>::Type;

    ///

    template<class T>
    inline constexpr bool IsVoid = IsSame<void, RemoveConstVolatile<T>>;


    ///

    template<typename >
    inline constexpr bool __IsIntegral = false;

    template<>
    inline constexpr bool __IsIntegral<bool> = true;

    template<typename T>
    inline constexpr bool IsIntegral = true;

    ///

    template<typename T>
    inline constexpr bool IsSigned = IsSame<T, MakeSigned<T>>;
}

using Core::Detail::FalseType;
using Core::Detail::IsIntegral;
using Core::Detail::IsLValueReference;
using Core::Detail::IsSigned;

#endif