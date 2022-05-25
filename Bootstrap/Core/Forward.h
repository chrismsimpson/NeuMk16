/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2022, chris@deepscroll.com
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef FORWARD_H
#define FORWARD_H

#include "Types.h"

namespace Core {

    namespace Detail {
    
        template<size_t inline_capacity>
        class ByteBuffer;
    }

    ///

    class Bitmap;
    using ByteBuffer = Core::Detail::ByteBuffer<32>;
    class Error;
    class GenericLexer;
    class String;
    class StringBuilder;
    class StringImpl;
    class StringView;
    class Time;
    class Utf8CodePointIterator;
    class Utf8View;

    ///

    template<typename T>
    class Span;

    ///

    template<typename T>
    using ReadOnlySpan = Span<const T>;

    ///

    template<typename T, size_t Size>
    struct LinearArray;

    ///

    template<typename Container, typename ValueType>
    class SimpleIterator;

    ///

    using Bytes = Span<u8>;

    using ReadOnlyBytes = ReadOnlySpan<u8>;

    ///

    template<typename T, Core::MemoryOrder DefaultMemoryOrder>
    class Atomic;

    ///

    template<typename T>
    struct Traits;

    ///

    template<typename T, typename TraitsForT = Traits<T>, bool IsOrdered = false>
    class HashTable;

    template<typename T, typename TraitsForT = Traits<T>>
    using OrderedHashTable = HashTable<T, TraitsForT, true>;

    template<typename K, typename V, typename KeyTraits = Traits<K>, bool IsOrdered = false>
    class HashMap;

    template<typename T, typename TraitsForT = Traits<T>, bool IsOrdered = false>
    class Set;

    template<typename K, typename V, typename KeyTraits = Traits<K>>
    using OrderedHashMap = HashMap<K, V, KeyTraits, true>;

    template<typename T>
    class Badge;

    template<size_t precision, typename Underlying = i32>
    class FixedPoint;

    template<typename>
    class Function;

    template<typename Out, typename... In>
    class Function<Out(In...)>;

    template<typename T>
    class NonNullRefPointer;

    template<typename T>
    class NonNullOwnPointer;

    template<typename T>
    class Optional;

    template<typename T>
    class RefPointer;

    template<typename T>
    class OwnPointer;

    template<typename T>
    class WeakPointer;

    template<typename T, size_t inline_capacity = 0>
    requires(!IsRValueReference<T>) class Vector;

    template<typename T, typename ErrorType = Error>
    class [[nodiscard]] ErrorOr;
}


using Core::Atomic;
using Core::Badge;
using Core::Bitmap;
using Core::ByteBuffer;
using Core::Bytes;
using Core::Error;
using Core::ErrorOr;
using Core::FixedPoint;
using Core::Function;
using Core::GenericLexer;
using Core::HashMap;
using Core::HashTable;
using Core::LinearArray;
using Core::NonNullOwnPointer;
using Core::NonNullRefPointer;
using Core::Optional;
using Core::OwnPointer;
using Core::ReadOnlyBytes;
using Core::RefPointer;
using Core::Span;
using Core::String;
using Core::StringBuilder;
using Core::StringImpl;
using Core::StringView;
using Core::Time;
using Core::Traits;
using Core::Utf8CodePointIterator;
using Core::Utf8View;
using Core::Vector;

#endif