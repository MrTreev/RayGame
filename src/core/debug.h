#pragma once
#include "core/config.h"
#include <cstdlib>
#include <string>
#include <typeinfo>

#if defined(RAYGAME_CC_GCC) || defined(RAYGAME_CC_CLANG)
#    include <cxxabi.h>
#endif

namespace core::debug {

template<typename T>
constexpr std::string type_name(T item) {
    if constexpr (core::config::COMPILER_IS_GCC_LIKE) {
        char* demangled_name =
            abi::__cxa_demangle(typeid(item).name(), nullptr, nullptr, nullptr);
        std::string ret_name{demangled_name};
        free(demangled_name);
        return ret_name;
    } else {
        return {typeid(item).name()};
    }
}

template<typename T>
constexpr std::string type_name() {
    const T item{};
    if constexpr (core::config::COMPILER_IS_GCC_LIKE) {
        char* demangled_name =
            abi::__cxa_demangle(typeid(item).name(), nullptr, nullptr, nullptr);
        std::string ret_name{demangled_name};
        free(demangled_name);
        return ret_name;
    } else {
        return {typeid(item).name()};
    }
}

} // namespace core::debug
