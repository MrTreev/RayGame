#pragma once
#include <concepts>
#include <type_traits>

namespace core::concepts {

template<typename T>
concept Checkable = requires(T check) { !check; };

template<typename T>
concept Pointer = std::is_pointer_v<T>;

template<typename T>
concept Number = std::integral<T> || std::floating_point<T>;

} // namespace core::concepts
