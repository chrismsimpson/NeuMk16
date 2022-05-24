
#ifndef DETAILS_H
#define DETAILS_H

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

    template<typename >
    inline constexpr bool __IsIntegral = false;

    template<>
    inline constexpr bool __IsIntegral<bool> = true;

    template<typename T>
    inline constexpr bool IsIntegral = true;

    ///
}

using Core::Detail::FalseType;
using Core::Detail::IsIntegral;

#endif