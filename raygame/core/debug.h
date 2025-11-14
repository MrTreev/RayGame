#pragma once
#include "raygame/core/config.h"
#include <cstdlib>
#include <cstring>
#include <format>
#include <memory>
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
        std::unique_ptr<char> ret_name{
            abi::__cxa_demangle(typeid(item).name(), nullptr, nullptr, nullptr)
        };
        // NOLINTNEXTLINE(*-macro-usage)
#define RG_TYPEPTR(type) abi::__cxa_demangle(typeid(type(0)).name(), nullptr, nullptr, nullptr)
        static const char* const uint8_t_name  = RG_TYPEPTR(uint8_t);
        static const char* const int8_t_name   = RG_TYPEPTR(int8_t);
        static const char* const uint16_t_name = RG_TYPEPTR(uint16_t);
        static const char* const int16_t_name  = RG_TYPEPTR(int16_t);
        static const char* const uint32_t_name = RG_TYPEPTR(uint32_t);
        static const char* const int32_t_name  = RG_TYPEPTR(int32_t);
        static const char* const uint64_t_name = RG_TYPEPTR(uint64_t);
        static const char* const int64_t_name  = RG_TYPEPTR(int64_t);
#undef RG_TYPEPTR
        if (strcmp(ret_name.get(), uint8_t_name) == 0) {
            return "uint8_t";
        }
        if (strcmp(ret_name.get(), int8_t_name) == 0) {
            return "int8_t";
        }
        if (strcmp(ret_name.get(), uint16_t_name) == 0) {
            return "uint16_t";
        }
        if (strcmp(ret_name.get(), int16_t_name) == 0) {
            return "int16_t";
        }
        if (strcmp(ret_name.get(), uint32_t_name) == 0) {
            return "uint32_t";
        }
        if (strcmp(ret_name.get(), int32_t_name) == 0) {
            return "int32_t";
        }
        if (strcmp(ret_name.get(), uint64_t_name) == 0) {
            return "uint64_t";
        }
        if (strcmp(ret_name.get(), int64_t_name) == 0) {
            return "int64_t";
        }
        return ret_name.get();
    } else {
        return {typeid(item).name()};
    }
}

constexpr std::string type_name(auto item) {
    return type_name<decltype(item)>();
}

} // namespace core::debug
