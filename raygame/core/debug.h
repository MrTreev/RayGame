#pragma once
#include "raygame/core/config.h"
#include <cstdlib>
#include <cstring>
#include <format>
#include <source_location>
#include <string>
#include <typeinfo>

#if defined(RAYGAME_CC_GCC) || defined(RAYGAME_CC_CLANG)
#    include <cxxabi.h>
#endif

namespace core::debug {
enum class SourceLoc : uint8_t {
    NONE = 0,
    FULL,
    BASE,
};
#if defined(RAYGAME_ENABLE_SOURCE_LOCATION)
constexpr SourceLoc sloc_type = SourceLoc::FULL;
#elif defined(RAYGAME_DISABLE_SOURCE_LOCATION)
#    if defined(NDEBUG)
constexpr SourceLoc sloc_type = SourceLoc::NONE;
#    else
constexpr SourceLoc sloc_type = SourceLoc::BASE;
#    endif
#else
#    warning "No source location macro defined, disabling"
constexpr SourceLoc sloc_type = SourceLoc::BASE;
#endif

constexpr std::string location_message(std::source_location loc) {
    constexpr std::string_view search_str = []() {
        if constexpr (debug::sloc_type == SourceLoc::FULL) {
            return "/raygame/";
        } else {
            return "/";
        }
    }();
    std::string_view shortloc{loc.file_name()};
    shortloc.remove_prefix(
        std::string_view(loc.file_name()).rfind(search_str) + search_str.length()
    );
    return std::format("{}:{}", shortloc, loc.line());
}

template<typename T>
constexpr std::string type_name() {
    const T item{};
    if constexpr (core::config::COMPILER_IS_GCC_LIKE) {
        char* demangled_name = abi::__cxa_demangle(typeid(item).name(), nullptr, nullptr, nullptr);
        std::string ret_name{demangled_name};
        free(demangled_name); //NOLINT(*-no-malloc,*-owning-memory)
        if (ret_name == "unsigned char") {
            return "uint8_t";
        }
        if (ret_name == "signed char") {
            return "int8_t";
        }
        if (ret_name == "unsigned short") {
            return "uint16_t";
        }
        if (ret_name == "short") {
            return "int16_t";
        }
        if (ret_name == "unsigned int") {
            return "uint32_t";
        }
        if (ret_name == "int") {
            return "int32_t";
        }
        if (ret_name == "unsigned long") {
            return "uint64_t";
        }
        if (ret_name == "long") {
            return "int64_t";
        }
        return ret_name;
    } else {
        return {typeid(item).name()};
    }
}

constexpr std::string type_name(auto item) {
    return type_name<decltype(item)>();
}

} // namespace core::debug
