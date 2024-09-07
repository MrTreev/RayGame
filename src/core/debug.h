#pragma once
#include "core/config.h"
#include <cstdlib>
#include <string>

#if defined(RAYGAME_CC_GCC) || defined(RAYGAME_CC_CLANG)
#    include <cxxabi.h>
#    include <typeinfo>
#endif

namespace core::debug {

template<typename T>
inline constexpr std::string type_name() {
    int         status = 0;
    std::string tname  = typeid(T).name();
#if defined(RAYGAME_CC_GCC) || defined(RAYGAME_CC_CLANG)
    char* demangled_name =
        abi::__cxa_demangle(tname.c_str(), nullptr, nullptr, &status);
    if (status == 0) {
        tname = demangled_name;
        free(demangled_name);
    }
#endif
    return tname;
}

} // namespace core::debug
