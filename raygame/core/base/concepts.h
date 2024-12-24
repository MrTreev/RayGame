#pragma once
#include <type_traits>

namespace core::concepts {

template<typename T>
concept Checkable = requires(T t) { !t; };

template<typename T>
concept Pointer = std::is_pointer_v<T>;

} // namespace core::concepts
