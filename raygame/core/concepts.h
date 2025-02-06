#pragma once
#include <concepts>
#include <iterator>
#include <type_traits>

namespace core::concepts {

//! A type that can be inverted and evaluated as a boolean
template<typename T>
concept Checkable = requires(T check) {
    { !check } -> std::same_as<bool>;
};

//! A type that is a pointer type
template<typename T>
concept Pointer = std::is_pointer_v<T>;

//! A type that is either an integral or floating-point type
template<typename T>
concept Number = std::integral<T> || std::floating_point<T>;

//! An iterator that supports advancement in constant-time and subscripting
template<typename T>
concept RandomAccessIterator = std::random_access_iterator<T>;

//! An iterator where the elements are contiguous in memory
template<typename T>
concept ContiguousIterator = std::contiguous_iterator<T>;

} // namespace core::concepts
