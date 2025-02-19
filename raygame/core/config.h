#pragma once
#include <cstddef>
#include <cstdint>

// NOLINTBEGIN(*-macro-usage)

/*!
 *  @defgroup macros_machine Machine-Specific Macros
 *  Macros used to specify machine-specific traits/features
 */

// clang-format off
#define RAYGAME_CPP_00 199711L
#define RAYGAME_CPP_11 201103L
#define RAYGAME_CPP_14 201402L
#define RAYGAME_CPP_17 201703L
#define RAYGAME_CPP_20 202002L
#define RAYGAME_CPP_23 202302L
// clang-format on

#if !defined(RAYGAME_MIN_CPP_VERSION)
#    define RAYGAME_MIN_CPP_VERSION RAYGAME_CPP_23
#endif

#if RAYGAME_MIN_CPP_VERSION <= 0
#elif RAYGAME_MIN_CPP_VERSION <= RAYGAME_CPP_00
#    define RAYGAME_CPP_STR "C++11"
#elif RAYGAME_MIN_CPP_VERSION <= RAYGAME_CPP_11
#    define RAYGAME_CPP_STR "C++11"
#elif RAYGAME_MIN_CPP_VERSION <= RAYGAME_CPP_14
#    define RAYGAME_CPP_STR "C++14"
#elif RAYGAME_MIN_CPP_VERSION <= RAYGAME_CPP_17
#    define RAYGAME_CPP_STR "C++17"
#elif RAYGAME_MIN_CPP_VERSION <= RAYGAME_CPP_20
#    define RAYGAME_CPP_STR "C++20"
#elif RAYGAME_MIN_CPP_VERSION <= RAYGAME_CPP_23
#    define RAYGAME_CPP_STR "C++23"
#endif

#if (__cplusplus < RAYGAME_MIN_CPP_VERSION)
static_assert(
    false,
    "This game's code uses features from the " RAYGAME_CPP_STR " standard"
);
#endif

#if !__has_include(<source_location>)
#    error "source_location unsupported, cannot continue"
#endif

#undef RAYGAME_CPP_00
#undef RAYGAME_CPP_11
#undef RAYGAME_CPP_14
#undef RAYGAME_CPP_17
#undef RAYGAME_CPP_20
#undef RAYGAME_CPP_23
#undef RAYGAME_CPP_STR
#undef RAYGAME_MIN_CPP_VERSION

//=============================================================================
// User-Configurable Macros
//=============================================================================
/*!
 *  @defgroup macros_config Configuration Macros
 *  User-defined configuration macros
 */

#if !defined(RAYGAME_TIME_FRAMES)
//! @ingroup macros_config
//! Log the average frame time
#    define RAYGAME_TIME_FRAMES false
#endif

#if !defined(RAYGAME_FORCE_GENERIC_IMPL)
//! @ingroup macros_config
//! Force generic implementations of operations
/*!
 *  Used for Testing, ignores compiler-specific optimisations in some functions
 */
#    define RAYGAME_FORCE_GENERIC_IMPL false
#endif

/*!
 *  @ingroup macros_config
 *  @defgroup macros_config_window_defaults Window Creation Defaults
 *  Defaults for window creation
 *  @{
 */
#if !defined(RAYGAME_DEFAULT_WINDOW_WIDTH)
//! Default Window Width
#    define RAYGAME_DEFAULT_WINDOW_WIDTH 640
#endif
#if !defined(RAYGAME_DEFAULT_WINDOW_HEIGHT)
//! Default Window Height
#    define RAYGAME_DEFAULT_WINDOW_HEIGHT 480
#endif
#if !defined(RAYGAME_DEFAULT_WINDOW_TITLE)
//! Default Window Title
#    define RAYGAME_DEFAULT_WINDOW_TITLE "RayGame"
#endif
//! @}

#if !defined(RAYGAME_TARGET_FPS)
#    define RAYGAME_TARGET_FPS 60
#endif

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
#    define RAYGAME_RANDOM_INITIAL_SEED 42
#endif

#if defined(RAYGAME_LOG_TRACE)
#    define RAYGAME_LOG_LEVEL TRACE
#elif defined(RAYGAME_LOG_DEBUG)
#    define RAYGAME_LOG_LEVEL DEBUG
#elif defined(RAYGAME_LOG_INFO)
#    define RAYGAME_LOG_LEVEL INFO
#elif defined(RAYGAME_LOG_NOTE)
#    define RAYGAME_LOG_LEVEL NOTE
#elif defined(RAYGAME_LOG_PROGRESS)
#    define RAYGAME_LOG_LEVEL PROGRESS
#elif defined(RAYGAME_LOG_WARNING)
#    define RAYGAME_LOG_LEVEL WARNING
#elif defined(RAYGAME_LOG_ERROR)
#    define RAYGAME_LOG_LEVEL ERROR
#elif defined(RAYGAME_LOG_FATAL)
#    define RAYGAME_LOG_LEVEL FATAL
#else
#    warning "No logging level set for RAYGAME, using NOTE"
constexpr Level logging_level = Level::NOTE;
#endif
//! @}

namespace core::log {
//! Logging level
enum class Level : uint8_t {
    TRACE    = 0,
    DEBUG    = 10,
    INFO     = 20,
    NOTE     = 30,
    PROGRESS = 40,
    /* 50 - 80 */
    WARNING  = 80,
    ERROR    = 90,
    FATAL    = 255,
};

constexpr Level logging_level = Level::RAYGAME_LOG_LEVEL;
} // namespace core::log

namespace core::config {
//! Log the average frame time
constexpr bool TIME_FRAMES = RAYGAME_TIME_FRAMES;

//! Game's target FPS
constexpr size_t TARGET_FPS = RAYGAME_TARGET_FPS;

//! Force generic implementations
constexpr bool FORCE_GENERIC_IMPL = RAYGAME_FORCE_GENERIC_IMPL;
} // namespace core::config

//=============================================================================
// Assertion
//=============================================================================
#if !defined(RAYGAME_ASSERT)
#    include <cassert>

#    define RAYGAME_ASSERT(condition, ...)                                     \
        assert(condition __VA_OPT__(, ) __VA_ARGS__)
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

#if defined(__amd64__) || defined(_M_X64_M_AMD64) || defined(__x86_64__)       \
    || defined(_M_X64)
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
#elif defined(RAYGAME_CC_GCC)
#    define RAYGAME_COMPILER GCC;
#elif defined(RAYGAME_CC_MINGW)
#    define RAYGAME_COMPILER MINGW;
#elif defined(RAYGAME_CC_MSC)
#    define RAYGAME_COMPILER MSC;
#endif

#define RAYGAME_PP_MACRO_STRINGIFY(x) RAYGAME_PP_STRINGIFY(x)
#define RAYGAME_PP_STRINGIFY(x)       #x

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
constexpr bool COMPILER_IS_GCC_LIKE =
    (COMPILER == Compiler::GCC || COMPILER == Compiler::CLANG);
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
#    define RAYGAME_OS_HURD
#    define RAYGAME_OS_LINUX
#    define RAYGAME_OS_MAC
#    define RAYGAME_OS_QNX
#    define RAYGAME_OS_TEMPLEOS
#    define RAYGAME_OS_WIN32
#    define RAYGAME_OS_WIN64
#endif
//! @}

#if (__STDC_HOSTED__ == 1)
#    if defined(__ANDROID__)
#        define RAYGAME_OS_ANDROID
#    elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)  \
        || defined(__bsdi__)
#        define RAYGAME_OS_BSD
#    elif defined(__GNU__) || defined(__gnu_hurd__)
#        define RAYGAME_OS_HURD
#        warning "Imagine using hurd, who are you? Richard Stallman?"
#    elif defined(__gnu_linux__) || defined(__linux__)
#        define RAYGAME_OS_LINUX
#    elif defined(macintosh) || defined(Macintosh)                             \
        || (defined(__APPLE__) && defined(__MACH__))
#        define RAYGAME_OS_MAC
#    elif defined(__QNX__) || defined(__QNXNTO__)
#        define RAYGAME_OS_QNX
#        warning "Why? Just why?"
#        warning "What possessed you to try running games on QNX?"
#    elif defined(_WIN64)
#        define RAYGAME_OS_WIN64
#        warning "Imagine using a niche videogame operating system..."
#        warning "Couldn't be me"
#    elif defined(_WIN32)
#        define RAYGAME_OS_WIN32
#        warning "Imagine using a niche videogame operating system..."
#        warning                                                               \
            "Couldn't be me, but at least the 32-bit versions"                 \
            " generally didn't have as much spyware"
#    else
static_assert(false, "Unknown Operating System");
#    endif
#else
static_assert(false, "Cannot run without an OS");
#endif

#if (__STDC_HOSTED__ != 1)
static_assert(false, "Cannot run without an OS");
#elif defined(RAYGAME_OS_ANDROID)
static_assert(false, "Not tested on Android yet");
#elif defined(RAYGAME_OS_BSD)
static_assert(false, "Not tested on BSD yet");
#elif defined(RAYGAME_OS_HURD)
static_assert(false, "Not tested on HURD");
#elif defined(RAYGAME_OS_LINUX)
static_assert(true);
#elif defined(RAYGAME_OS_MAC)
static_assert(false, "Not tested on Apple Macintosh");
#elif defined(RAYGAME_OS_QNX)
static_assert(false, "Not tested on QNX");
#elif defined(RAYGAME_OS_TEMPLEOS)
#elif defined(RAYGAME_OS_WIN32)
static_assert(false, "Not tested on Windows 32-bit yet");
#elif defined(RAYGAME_OS_WIN64)
static_assert(false, "Not tested on Windows 64-bit yet");
#else
static_assert(false, "Unknown Operating System");
#endif

namespace core::config {
//! Operating System Definitions
enum class OperatingSystem : uint8_t {
    ANDROID,  //!< Android OS
    BSD,      //!< BSD
    HURD,     //!< GNU Hurd
    LINUX,    //!< Linux
    MAC,      //!< Mac OS
    QNX,      //!< QNX RTOS
    TEMPLEOS, //!< TempleOS
    WIN32,    //!< Windows 32-Bit
    WIN64,    //!< Windows 64-Bit
};

namespace detail {
consteval OperatingSystem get_os() {
#if defined(RAYGAME_OS_ANDROID)
    return OperatingSystem::ANDROID;
#elif defined(RAYGAME_OS_BSD)
    return OperatingSystem::BSD;
#elif defined(RAYGAME_OS_HURD)
    return OperatingSystem::HURD;
#elif defined(RAYGAME_OS_LINUX)
    return OperatingSystem::LINUX;
#elif defined(RAYGAME_OS_MAC)
    return OperatingSystem::MAC;
#elif defined(RAYGAME_OS_QNX)
    return OperatingSystem::QNX;
#elif defined(RAYGAME_OS_TEMPLEOS)
    return OperatingSystem::TEMPLEOS;
#elif defined(RAYGAME_OS_WIN32)
    return OperatingSystem::WIN32;
#elif defined(RAYGAME_OS_WIN64)
    return OperatingSystem::WIN64;
#endif
}
} // namespace detail

constexpr OperatingSystem OPERATING_SYSTEM = detail::get_os();

} // namespace core::config

//=============================================================================
// Build Type Config
//=============================================================================
namespace core::config::detail {
consteval bool debug() {
#if defined(NDEBUG)
    return false;
#else
    return true;
#endif
}
} // namespace core::config::detail

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

constexpr BuildType BUILD_TYPE =
    detail::debug() ? BuildType::DEBUG : BuildType::RELEASE;
} // namespace core::config

//=============================================================================
// SIMD Config
//=============================================================================
namespace core::config::simd {

consteval bool avx();      //!< SIMD supports AVX
consteval bool avx2();     //!< SIMD supports AVX2
consteval bool float256(); //!< SIMD supports 256-bit float operations
consteval bool neon();     //!< SIMD supports ARM NEON
consteval bool simd128();  //!< SIMD supports 128-bit integer operations
consteval bool sse2();     //!< SIMD supports SSE2
consteval bool ssse3();    //!< SIMD supports SSSE3
consteval bool x256();     //!< SIMD supports 256-bit integer operations

consteval bool sse2() {
#if defined(__SSE2__)
    return true;
#else
    return false;
#endif
}

consteval bool avx() {
#if defined(__AVX__)
    return true;
#else
    return false;
#endif
}

consteval bool avx2() {
#if defined(__AVX2__)
    return true;
#else
    return false;
#endif
}

consteval bool ssse3() {
#if defined(__SSSE3__)
    return true;
#else
    return false;
#endif
}

consteval bool neon() {
#if defined(__ARM_NEON)
    return true;
#else
    return false;
#endif
}

consteval bool simd128() {
#if defined(RAYGAME_HAS_NEON) || defined(RAYGAME_HAS_SSE2)
    return true;
#else
    return false;
#endif
}

consteval bool float256() {
#if defined(RAYGAME_HAS_AVX)
    return true;
#else
    return false;
#endif
}

consteval bool x256() {
#if defined(RAYGAME_HAS_AVX2)
    return true;
#else
    return false;
#endif
}
} // namespace core::config::simd

// NOLINTEND(*-macro-usage)
