#include "raygame/core/exception.h" // IWYU pragma: keep
#include "raygame/core/debug.h"

namespace core::exception {
// Honestly, just easier this way, macro is pretty obvious what it does
// NOLINTBEGIN(*-macro-usage)
#define RAYGAME_EXCEPTION_DEF(name) RAYGAME_EXCEPTION_DEF_BASE(name, Exception)
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

RAYGAME_EXCEPTION_DEF_BASE(Exception, std::runtime_error);

RAYGAME_EXCEPTION_DEF(Unimplemented);
RAYGAME_EXCEPTION_DEF(UnknownCase);
RAYGAME_EXCEPTION_DEF(Unreachable);

RAYGAME_EXCEPTION_DEF(Condition);
RAYGAME_EXCEPTION_DEF_BASE(PreCondition, Condition);
RAYGAME_EXCEPTION_DEF_BASE(CheckCondition, Condition);
RAYGAME_EXCEPTION_DEF_BASE(PostCondition, Condition);

} // namespace core::exception
