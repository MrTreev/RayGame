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
    const char* tname = typeid(item).name();
#if defined(RAYGAME_CC_GCC) || defined(RAYGAME_CC_CLANG)
    const char* demangled_name =
        abi::__cxa_demangle(tname, nullptr, nullptr, nullptr);
    tname = demangled_name;
#endif
    return {tname};
}

} // namespace core::debug
