#include "raygame/core/exception.h" // IWYU pragma: keep
#include "raygame/core/debug.h"

namespace core::exception {
// Honestly, just easier this way, macro is pretty obvious what it does
// NOLINTBEGIN(*-macro-usage)
#define RAYGAME_EXCEPTION_DEF_BASE(name, base)                                 \
    name::name(const std::string& message)                                     \
        : base(message) {}                                                     \
    name::name(const base&& error)                                             \
        : base(error) {}                                                       \
    const char* name::type() {                                                 \
        static const std::string typestring{debug::type_name(this)};           \
        return typestring.c_str();                                             \
    }                                                                          \
    name::~name() = default

// NOLINTEND(*-macro-usage)

Exception ::Exception(const std ::string& message)
    : std ::runtime_error(message) {}

Exception ::Exception(const std ::runtime_error&& error)
    : std ::runtime_error(error) {}

const char* Exception::type() {
    static const std::string typestring{debug::type_name(this)};
    return typestring.c_str();
}

Exception ::~Exception() = default;

RAYGAME_EXCEPTION_DEF_BASE(Unimplemented, Exception);
RAYGAME_EXCEPTION_DEF_BASE(UnknownCase, Exception);
RAYGAME_EXCEPTION_DEF_BASE(Unreachable, Exception);

RAYGAME_EXCEPTION_DEF_BASE(Condition, Exception);
RAYGAME_EXCEPTION_DEF_BASE(PreCondition, Condition);
RAYGAME_EXCEPTION_DEF_BASE(CheckCondition, Condition);
RAYGAME_EXCEPTION_DEF_BASE(PostCondition, Condition);

} // namespace core::exception
