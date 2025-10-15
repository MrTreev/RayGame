#pragma once
#include "raygame/core/macros.h"
#include <cstddef>
#include <cstdint>

//=============================================================================
// Machine-Specific Macros
//=============================================================================

/*!
 *  @defgroup macros_machine Machine-Specific Macros
 *  Macros used to specify machine-specific traits/features
 */

// preprocessor doesn't allow apostrophe separated numbers
// clang-format off
#if (__cplusplus < 202302L)
// clang-format on
static_assert(false, "This game's code uses features from the C++23 standard");
#endif

#if !__has_include(<source_location>)
#    error "source_location unsupported, cannot continue"
#endif

//=============================================================================
// User-Configurable Macros
//=============================================================================
/*!
 *  @defgroup macros_config Configuration Macros
 *  User-defined configuration macros
 */

/*!
 *  @ingroup macros_config
 *  @defgroup macros_config_random Random Number Generator
 *  Configuration macros for the random number generator
 *  @{
 */

#if !defined(RAYGAME_USE_FULL_RANDOM)
//! Use non-deterministic randomness
/*!
 *  Non-deterministic mode uses the C++ `std::random_device` as the seed for RNG.
 *  Deterministic mode uses a fixed value as the seed, incrementing each time it
 *  is accessed.
 */
#    define RAYGAME_USE_FULL_RANDOM false
#endif

#if !defined(RAYGAME_RANDOM_INITIAL_SEED)
//! Initial seed for randomness when in deterministic mode (uint64_t)
#    define RAYGAME_RANDOM_INITIAL_SEED 42 // NOLINT(*-macro-usage)
#endif

//=============================================================================
// Architecture Config
//=============================================================================
//! @ingroup macros_machine
//! @defgroup macros_machine_architecture Architecture
//! @{
#if defined(RAYGAME_DOXYGEN_INVOKED)
#    define RAYGAME_ARCH_X86_64
#    define RAYGAME_ARCH_X86_32
#    define RAYGAME_ARCH_RISCV
#    define RAYGAME_ARCH_ARM64
#    define RAYGAME_ARCH_ARM
#endif
//! @}

#if defined(__amd64__) || defined(_M_X64_M_AMD64) || defined(__x86_64__) || defined(_M_X64)
#    define RAYGAME_ARCH_X86_64
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
#    define RAYGAME_ARCH_X86_32
#elif defined(__rixscv) || defined(__rixscv_xlen)
#    define RAYGAME_ARCH_RISCV
static_assert(false, "Not tested on RISCV yet");
#elif defined(__aarch64) || defined(_M_ARM64)
#    define RAYGAME_ARCH_ARM64
static_assert(false, "Not tested on ARM64 yet");
#elif defined(__arm__) || defined(_M_ARM)
#    define RAYGAME_ARCH_ARM
static_assert(false, "Not tested on ARM yet");
#else
static_assert(false, "Unknown Architecture");
#endif

#if defined(RAYGAME_ARCH_X86_64)
static_assert(true);
#elif defined(RAYGAME_ARCH_X86_32)
static_assert(false, "Not tested on X86_32 yet");
#elif defined(RAYGAME_ARCH_RISCV)
static_assert(false, "Not tested on RISCV yet");
#elif defined(RAYGAME_ARCH_ARM64)
static_assert(false, "Not tested on ARM64 yet");
#elif defined(RAYGAME_ARCH_ARM)
static_assert(false, "Not tested on ARM yet");
#else
static_assert(false, "Unknown Architecture");
#endif

#if defined(RAYGAME_ARCH_X86_64)
#    define RAYGAME_ARCH X86_64
#elif defined(RAYGAME_ARCH_X86_32)
#    define RAYGAME_ARCH X86_32
#elif defined(RAYGAME_ARCH_RISCV)
#    define RAYGAME_ARCH RISCV;
#elif defined(RAYGAME_ARCH_ARM64)
#    define RAYGAME_ARCH ARM64;
#elif defined(RAYGAME_ARCH_ARM)
#    define RAYGAME_ARCH ARM;
#endif

namespace core::config {
//! Architecture Definitions
enum class Architecture : uint8_t {
    X86_64, //!< X86, 64-Bit
    X86_32, //!< X86, 32-Bit
    ARM,    //!< ARM, 32-Bit
    ARM64,  //!< ARM, 64-Bit
    RISCV,  //!< RISCV
};

constexpr Architecture ARCHITECTURE = Architecture::RAYGAME_ARCH;
} // namespace core::config

//=============================================================================
// Endian Config
//=============================================================================
//! @ingroup macros_machine
//! @defgroup macros_machine_endian Endianness
//! @{
#if defined(RAYGAME_DOXYGEN_INVOKED)
#    define RAYGAME_LITTLE_ENDIAN
#    define RAYGAME_BIG_ENDIAN
#endif
//! @}

#if defined(__BYTE_ORDER__)
#    if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#        define RAYGAME_LITTLE_ENDIAN
#    elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#        define RAYGAME_BIG_ENDIAN
#    endif
#endif

#if defined(RAYGAME_LITTLE_ENDIAN)
#    define RAYGAME_ENDIAN LITTLE
#elif defined(RAYGAME_BIG_ENDIAN)
#    define RAYGAME_ENDIAN BIG
#endif

namespace core::config {
//! Endian Definitions
enum class Endian : uint8_t {
    LITTLE, //!< Little-Endian
    BIG,    //!< Big-Endian
};
constexpr Endian ENDIANNESS = Endian::RAYGAME_ENDIAN;
} // namespace core::config

//=============================================================================
// Compiler Config
//=============================================================================
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

#if defined(RAYGAME_CC_CLANG)
#    define RAYGAME_COMPILER CLANG;
#    define RAYGAME_INLINE   __attribute__((always_inline))
#elif defined(RAYGAME_CC_GCC)
#    define RAYGAME_COMPILER GCC;
#    define RAYGAME_INLINE   __attribute__((always_inline))
#elif defined(RAYGAME_CC_MINGW)
#    define RAYGAME_COMPILER MINGW;
#    define RAYGAME_INLINE   inline
#elif defined(RAYGAME_CC_MSC)
#    define RAYGAME_COMPILER MSC;
#    define ZPP_BITS_INLINE  [[msvc::forceinline]]
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
#    define RAYGAME_CLANG_SUPPRESS_WARNING(warnstr)                                                \
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
#    define RAYGAME_GCC_SUPPRESS_WARNING(warnstr)                                                  \
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

namespace core::config {
//! Compiler Definitions
enum class Compiler : uint8_t {
    CLANG, //!< Clang-based compiler
    GCC,   //!< GCC-based compiler
    MSC,   //!< MSVC-based compiler
    MINGW, //!< MINGW-based compiler
};

constexpr Compiler COMPILER = Compiler::RAYGAME_COMPILER;

//! Compiler has GCC-like compiler features
constexpr bool COMPILER_IS_GCC_LIKE = (COMPILER == Compiler::GCC || COMPILER == Compiler::CLANG);
} // namespace core::config

//=============================================================================
// OS Config
//=============================================================================
//! @ingroup macros_machine
//! @defgroup macros_machine_os Operating System
//! @{
#if defined(RAYGAME_DOXYGEN_INVOKED)
#    define RAYGAME_OS_ANDROID
#    define RAYGAME_OS_BSD
#    define RAYGAME_OS_LINUX
#    define RAYGAME_OS_MAC
#    define RAYGAME_OS_WIN64
#endif
//! @}

#if (__STDC_HOSTED__ == 1)
#    if defined(__ANDROID__)
#        define RAYGAME_OS_ANDROID
#    elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
#        define RAYGAME_OS_BSD
#    elif defined(__gnu_linux__) || defined(__linux__)
#        define RAYGAME_OS_LINUX
#    elif defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
#        define RAYGAME_OS_MAC
#    elif defined(_WIN64)
#        define RAYGAME_OS_WIN64
#    endif
#else
static_assert(false, "Cannot run without an OS");
#endif

#if (__STDC_HOSTED__ != 1)
static_assert(false, "Cannot run without an OS");
#elif defined(RAYGAME_OS_ANDROID)
static_assert(false, "Not tested on Android");
#elif defined(RAYGAME_OS_BSD)
static_assert(false, "Not tested on BSD");
#elif defined(RAYGAME_OS_LINUX)
static_assert(true, "Tested with Linux");
#elif defined(RAYGAME_OS_MAC)
static_assert(false, "Not tested on Apple Macintosh");
#elif defined(RAYGAME_OS_WIN64)
static_assert(false, "Not tested on Windows");
#else
static_assert(false, "Unknown Operating System");
#endif

namespace core::config {
//! Operating System Definitions
enum class OperatingSystem : uint8_t {
    ANDROID, //!< Android OS
    BSD,     //!< BSD
    LINUX,   //!< Linux
    MAC,     //!< Mac OS
    WIN64,   //!< Windows 64-Bit
};

constexpr OperatingSystem OPERATING_SYSTEM = []() {
#if defined(RAYGAME_OS_ANDROID)
    return OperatingSystem::ANDROID;
#elif defined(RAYGAME_OS_BSD)
    return OperatingSystem::BSD;
#elif defined(RAYGAME_OS_LINUX)
    return OperatingSystem::LINUX;
#elif defined(RAYGAME_OS_MAC)
    return OperatingSystem::MAC;
#elif defined(RAYGAME_OS_WIN64)
    return OperatingSystem::WIN64;
#endif
}();

} // namespace core::config

//=============================================================================
// Build Type Config
//=============================================================================

#if defined(NDEBUG)
// NOLINTNEXTLINE(*-macro-usage)
#    define RAYGAME_RELEASE_ONLY(x) x
#    define RAYGAME_DEBUG_ONLY(x)
#else
// NOLINTNEXTLINE(*-macro-usage)
#    define RAYGAME_DEBUG_ONLY(x) x
#    define RAYGAME_RELEASE_ONLY(x)
#endif

namespace core::config {
enum class BuildType : bool {
    DEBUG,
    RELEASE,
};

constexpr BuildType BUILD_TYPE = []() {
#if defined(NDEBUG)
    return BuildType::RELEASE;
#else
    return BuildType::DEBUG;
#endif
}();
} // namespace core::config
