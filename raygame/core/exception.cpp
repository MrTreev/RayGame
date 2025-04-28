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
    std::string name::type() {                                           \
        return debug::type_name(this);                                         \
    }                                                                          \
    name::~name() = default

// NOLINTEND(*-macro-usage)

RAYGAME_EXCEPTION_DEF_BASE(Exception, std::runtime_error);
RAYGAME_EXCEPTION_DEF_BASE(Unimplemented, Exception);
RAYGAME_EXCEPTION_DEF_BASE(UnknownCase, Exception);
RAYGAME_EXCEPTION_DEF_BASE(Unreachable, Exception);

RAYGAME_EXCEPTION_DEF_BASE(Condition, Exception);
RAYGAME_EXCEPTION_DEF_BASE(PreCondition, Condition);
RAYGAME_EXCEPTION_DEF_BASE(CheckCondition, Condition);
RAYGAME_EXCEPTION_DEF_BASE(PostCondition, Condition);

} // namespace core::exception
