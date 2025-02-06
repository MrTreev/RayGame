#pragma once
//! @ingroup macros_machine
//! @defgroup macros_machine_compiler Compiler
//! @{
#if defined(RAYGAME_DOXYGEN_INVOKED)
#    define RAYGAME_CC_CLANG
#    define RAYGAME_CC_GCC
#    define RAYGAME_CC_MINGW
#    define RAYGAME_CC_MSC
#endif
//! @}

#if defined(__clang__)
#    define RAYGAME_CC_CLANG
#elif defined(__GNUC__)
#    define RAYGAME_CC_GCC
#elif defined(__MINGW32__)
#    define RAYGAME_CC_MINGW
#elif defined(_MSC_VER)
#    define RAYGAME_CC_MSC
#else
static_assert(false, "Unknown Compiler");
#endif

#if !defined(RAYGAME_CLANG_MIN)
// NOLINTNEXTLINE(*-macro-usage)
#    define RAYGAME_CLANG_MIN 19
#endif
#if (__clang_major__ < RAYGAME_CLANG_MIN)
#    error "Only tested on clang " RAYGAME_PP_MACRO_STRINGIFY(RAYGAME_CLANG_MIN) " and higher"
#endif
#undef RAYGAME_CLANG_MIN

//=============================================================================
// Compiler-Dependant Pragma Macros
//=============================================================================

//! @defgroup macros_machine_pragma Pragma macros
//! push, string, pop pragmas for suppressing compiler warnings
//! @{
// NOLINTBEGIN(*-macro-usage)
#if defined(RAYGAME_CC_CLANG) && !defined(RAYGAME_DOXYGEN_INVOKED)
#    define RAYGAME_PRAGMA_TO_STR(x)            _Pragma(#x)
#    define RAYGAME_CLANG_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
#    define RAYGAME_CLANG_SUPPRESS_WARNING(warnstr)                            \
        RAYGAME_PRAGMA_TO_STR(clang diagnostic ignored warnstr)
#    define RAYGAME_CLANG_SUPPRESS_WARNING_POP _Pragma("clang diagnostic pop")
#else
#    define RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
#    define RAYGAME_CLANG_SUPPRESS_WARNING(warnstr)
#    define RAYGAME_CLANG_SUPPRESS_WARNING_POP
#endif
#if defined(RAYGAME_CC_GCC) && !defined(RAYGAME_DOXYGEN_INVOKED)
#    define RAYGAME_PRAGMA_TO_STR(x)          _Pragma(#x)
#    define RAYGAME_GCC_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
#    define RAYGAME_GCC_SUPPRESS_WARNING(warnstr)                              \
        RAYGAME_PRAGMA_TO_STR(GCC diagnostic ignored warnstr)
#    define RAYGAME_GCC_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
#else
#    define RAYGAME_GCC_SUPPRESS_WARNING_PUSH
#    define RAYGAME_GCC_SUPPRESS_WARNING(warnstr)
#    define RAYGAME_GCC_SUPPRESS_WARNING_POP
#endif
#if defined(RAYGAME_CC_MSC) && !defined(RAYGAME_DOXYGEN_INVOKED)
#    define RAYGAME_MSC_SUPPRESS_WARNING_PUSH     __pragma(warning(push))
#    define RAYGAME_MSC_SUPPRESS_WARNING(warnstr) __pragma(warning(disable : w))
#    define RAYGAME_MSC_SUPPRESS_WARNING_POP      __pragma(warning(pop))
#else
#    define RAYGAME_MSC_SUPPRESS_WARNING_PUSH
#    define RAYGAME_MSC_SUPPRESS_WARNING(warnstr)
#    define RAYGAME_MSC_SUPPRESS_WARNING_POP
#endif
// NOLINTEND(*-macro-usage)
//! @}
