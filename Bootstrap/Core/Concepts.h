
#ifndef CONCEPTS_H
#define CONCEPTS_H

#include "Forward.h"
#include "IterationDecision.h"
#include "Extras.h"

namespace Core::Concepts {
    
    template<typename T>
    concept Integral = IsIntegral<T>;
    
    ///

    template<typename T>
    concept FloatingPoint = IsFloatingPoint<T>;

    ///

    template<typename T>
    concept Fundamental = IsFundamental<T>;

    ///

    template<typename T>
    concept Arithmetic = IsArithmetic<T>;

    ///

    template<typename T>
    concept Signed = IsSigned<T>;

    ///

    template<typename T>
    concept Unsigned = IsUnsigned<T>;

    ///

    template<typename T>
    concept Enum = IsEnum<T>;

    ///

    template<typename T, typename U>
    concept SameAs = IsSame<T, U>;

    ///

    template<typename U, typename... Ts>
    concept OneOf = IsOneOf<U, Ts...>;

    ///

    template<typename U, typename... Ts>
    concept OneOfIgnoringConstVolatile = IsOneOfIgnoringConstVolatile<U, Ts...>;

    ///

    template<typename T, template<typename...> typename S>
    concept SpecializationOf = IsSpecializationOf<T, S>;

    ///

    // template<typename T>
    // concept AnyString = Detail::IsConstructible<StringView, T>;

    ///

    template<typename T, typename U>
    concept HashCompatible = IsHashCompatible<Detail::Decay<T>, Detail::Decay<U>>;

    ///

    // Any indexable, sized, contiguous data structure.

    template<typename ArrayT, typename ContainedT, typename SizeT = size_t>
    concept ArrayLike = requires(ArrayT array, SizeT index) {

        {
            array[index]
        }
        -> SameAs<RemoveReference<ContainedT>&>;

        {
            array.size()
        }
        -> SameAs<SizeT>;

        {
            array.span()
        }
        -> SameAs<Span<RemoveReference<ContainedT>>>;

        {
            array.data()
        }
        -> SameAs<RemoveReference<ContainedT>*>;
    };

    ///

    template<typename Func, typename... Args>
    concept VoidFunction = requires(Func func, Args... args) {

        {
            func(args...)
        }
        -> SameAs<void>;
    };

    ///

    template<typename Func, typename... Args>
    concept IteratorFunction = requires(Func func, Args... args) {

        {
            func(args...)
        }
        -> SameAs<IterationDecision>;
    };

    ///

    template<typename T, typename EndT>
    concept IteratorPairWith = requires(T it, EndT end) {

        *it;
        { it != end } -> SameAs<bool>;
        ++it;
    };

    ///

    template<typename T>
    concept IterableContainer = requires {

        { declval<T>().begin() } -> IteratorPairWith<decltype(declval<T>().end())>;
    };
}

using Core::Concepts::Arithmetic;
using Core::Concepts::ArrayLike;
using Core::Concepts::Enum;
using Core::Concepts::FloatingPoint;
using Core::Concepts::Fundamental;
using Core::Concepts::Integral;
using Core::Concepts::IterableContainer;
using Core::Concepts::IteratorFunction;
using Core::Concepts::IteratorPairWith;
using Core::Concepts::OneOf;
using Core::Concepts::OneOfIgnoringConstVolatile;
using Core::Concepts::SameAs;
using Core::Concepts::Signed;
using Core::Concepts::SpecializationOf;
using Core::Concepts::Unsigned;
using Core::Concepts::VoidFunction;

#endif