#pragma once

#include <type_traits>

namespace core::concepts {

template<typename T>
concept checkable = requires(T t) { !t; };

template<typename T>
concept pointer = std::is_pointer_v<T>;

} // namespace core::concepts
