#pragma once
#include "core/base/config.h"
#include <cstdlib>
#include <string>
#include <typeinfo>

#if defined(RAYGAME_CC_GCC) || defined(RAYGAME_CC_CLANG)
#    include <cxxabi.h>
#endif

namespace core::debug {

template<typename T>
constexpr std::string type_name() {
    const T item{};
    if constexpr (core::config::COMPILER_IS_GCC_LIKE) {
        char* demangled_name =
            abi::__cxa_demangle(typeid(item).name(), nullptr, nullptr, nullptr);
        std::string ret_name{demangled_name};
        free(demangled_name);
        if (ret_name == "unsigned char") {
            return "uint8_t";
        } else if (ret_name == "signed char") {
            return "int8_t";
        } else if (ret_name == "unsigned short") {
            return "uint16_t";
        } else if (ret_name == "short") {
            return "int16_t";
        } else if (ret_name == "unsigned int") {
            return "uint32_t";
        } else if (ret_name == "int") {
            return "int32_t";
        } else if (ret_name == "unsigned long") {
            return "uint64_t";
        } else if (ret_name == "long") {
            return "int64_t";
        } else {
            return ret_name;
        }
    } else {
        return {typeid(item).name()};
    }
}

constexpr std::string type_name(auto item) {
    return type_name<decltype(item)>();
}

} // namespace core::debug
