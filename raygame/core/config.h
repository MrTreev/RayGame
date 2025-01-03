#pragma once
#include <cstdint>
#include <string>

//=============================================================================
// Feature Checking
//=============================================================================

// clang-format off
#if (__cplusplus < 202002L)
// clang-format on
static_assert(false, "This game's code uses features from the C++23 standard");
#endif

//=============================================================================
// User-Configurable Macros
//=============================================================================
#if defined(RAYGAME_DOXYGEN_INVOKED)
/*!
 *  @defgroup macros_config Configuration Macros
 *  User-defined configuration macros
 *  @{
 */

//! Force generic implementations of operations
/*!
 *  Used for Testing, ignores compiler-specific optimisations in some functions
 */
#    define RAYGAME_FORCE_GENERIC_IMPL

/*!
 *  @defgroup macros_config_window_backend Window Backend
 *  Set the window backend
 *  @{
 */
#    define RAYGAME_GUI_BACKEND_WAYLAND
#    define RAYGAME_GUI_BACKEND_X11
#    define RAYGAME_GUI_BACKEND_DWM
#    define RAYGAME_GUI_BACKEND_COCOA
//! @}

/*!
 *  @defgroup macros_config_window_defaults Window Creation Defaults
 *  Defaults for window creation
 *  @{
 */
//! Default Window Width
#    define RAYGAME_DEFAULT_WINDOW_WIDTH  640
//! Default Window Height
#    define RAYGAME_DEFAULT_WINDOW_HEIGHT 480
//! Default Window Title
#    define RAYGAME_DEFAULT_WINDOW_TITLE  "RayGame"
//! @}

/*!
 *  @defgroup macros_random Random Number Generator
 *  Configuration macros for the random number generator
 *  @{
 */

//! Use non-deterministic randomness
/*!
 *  Non-deterministic mode uses the C++ `std::random_device` as the seed for RNG.
 *  Deterministic mode uses a fixed value as the seed, incrementing each time it
 *  is accessed.
 */
#    define RAYGAME_USE_FULL_RANDOM

//! Initial seed for randomness when in deterministic mode (uint64_t)
#    define RAYGAME_RANDOM_INITIAL_SEED

//! @}
//! @}
#else
#    if !defined(RAYGAME_DEFAULT_WINDOW_WIDTH)
#        define RAYGAME_DEFAULT_WINDOW_WIDTH 640 // NOLINT(*-macro-usage)
#    endif
#    if !defined(RAYGAME_DEFAULT_WINDOW_HEIGHT)
#        define RAYGAME_DEFAULT_WINDOW_HEIGHT 480 // NOLINT(*-macro-usage)
#    endif
#    if !defined(RAYGAME_DEFAULT_WINDOW_TITLE)
#        define RAYGAME_DEFAULT_WINDOW_TITLE "RayGame" // NOLINT(*-macro-usage)
#    endif
#endif

namespace core::config {
#if defined(RAYGAME_FORCE_GENERIC_IMPL)
//! Force generic implementations
static constexpr bool FORCE_GENERIC_IMPL = true;
#else
//! Force generic implementations
static constexpr bool FORCE_GENERIC_IMPL = false;
#endif
} // namespace core::config

namespace core::window {
//! Default Window Width
static constexpr std::size_t DEFAULT_WINDOW_WIDTH =
    RAYGAME_DEFAULT_WINDOW_WIDTH;
//! Default Window Height
static constexpr std::size_t DEFAULT_WINDOW_HEIGHT =
    RAYGAME_DEFAULT_WINDOW_HEIGHT;
//! Default Window Title
static constexpr std::string DEFAULT_WINDOW_TITLE =
    RAYGAME_DEFAULT_WINDOW_TITLE;
} // namespace core::window

//=============================================================================
// Machine-Specific Macros
//=============================================================================
#if defined(RAYGAME_DOXYGEN_INVOKED)
/*!
 *  @defgroup macros_machine Machine-Specific macros
 *  Macros used to specify machine-specific traits/features
 *  @{
 */

//! @defgroup macros_machine_build_type Build Type
//! @{
#    define RAYGAME_BUILD_TYPE_RELEASE
#    define RAYGAME_BUILD_TYPE_DEBUG
//! @}

//! @defgroup macros_machine_architecture Architecture
//! @{
#    define RAYGAME_ARCH_X86_64
#    define RAYGAME_ARCH_X86_32
#    define RAYGAME_ARCH_RISCV
#    define RAYGAME_ARCH_ARM64
#    define RAYGAME_ARCH_ARM
//! @}

//! @defgroup macros_machine_endian Endianness
//! @{
#    define RAYGAME_LITTLE_ENDIAN
#    define RAYGAME_BIG_ENDIAN
//! @}

//! @defgroup macros_machine_compiler Compiler
//! @{
#    define RAYGAME_CC_CLANG
#    define RAYGAME_CC_GCC
#    define RAYGAME_CC_MINGW
#    define RAYGAME_CC_MSC
//! @}

//! @defgroup macros_machine_os Operating System
//! @{
#    define RAYGAME_OS_ANDROID
#    define RAYGAME_OS_BSD
#    define RAYGAME_OS_HURD
#    define RAYGAME_OS_MAC
#    define RAYGAME_OS_QNX
#    define RAYGAME_OS_WIN32
#    define RAYGAME_OS_WIN64
//! @}

//! @defgroup macros_machine_simd SIMD instructions
//! @{
#    define RAYGAME_HAS_SSE2
#    define RAYGAME_SIMD_128BIT
#    define RAYGAME_HAS_SSSE3
#    define RAYGAME_HAS_AVX
#    define RAYGAME_SIMD_256BIT_F
#    define RAYGAME_HAS_AVX2
#    define RAYGAME_SIMD_256BIT_X
#    define RAYGAME_HAS_NEON
//! @}

//! @}
#endif

#if !__has_include(<source_location>)
#    error "source_location unsupported, cannot continue"
#endif

#if !defined(RAYGAME_ASSERT)
#    include <cassert>
// NOLINTNEXTLINE(*-macro-usage)
#    define RAYGAME_ASSERT(...) assert(__VA_ARGS__)
#endif

//=============================================================================
// Architecture Config
//=============================================================================

namespace core::config {
//! Architecture Definitions
enum class Architecture : std::uint8_t {
    X86_64, //!< X86, 64-Bit
    X86_32, //!< X86, 32-Bit
    ARM,    //!< ARM, 32-Bit
    ARM64,  //!< ARM, 64-Bit
    RISCV,  //!< RISCV
};

#if defined(__amd64__) || defined(_M_X64_M_AMD64) || defined(__x86_64__)       \
    || defined(_M_X64)
#    define RAYGAME_ARCH_X86_64
static constexpr Architecture ARCHITECTURE = Architecture::X86_64;
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
#    define RAYGAME_ARCH_X86_32
static constexpr Architecture ARCHITECTURE = Architecture::X86_32;
#elif defined(__rixscv) || defined(__rixscv_xlen)
#    define RAYGAME_ARCH_RISCV
static constexpr Architecture ARCHITECTURE = Architecture::RISCV;
static_assert(false, "Not tested on RISCV yet");
#elif defined(__aarch64) || defined(_M_ARM64)
#    define RAYGAME_ARCH_ARM64
static constexpr Architecture ARCHITECTURE = Architecture::ARM64;
static_assert(false, "Not tested on ARM64 yet");
#elif defined(__arm__) || defined(_M_ARM)
#    define RAYGAME_ARCH_ARM
static constexpr Architecture ARCHITECTURE = Architecture::ARM;
static_assert(false, "Not tested on ARM yet");
#else
static_assert(false, "Unknown Architecture");
#endif
} // namespace core::config

//=============================================================================
// Endian Config
//=============================================================================

namespace core::config {
//! Endian Definitions
enum class Endian : std::uint8_t {
    LITTLE, //!< Little-Endian
    BIG,    //!< Big-Endian
};

#if defined(__BYTE_ORDER__)
#    if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#        define RAYGAME_LITTLE_ENDIAN
static constexpr Endian ENDIANNESS = Endian::LITTLE;
#    elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#        define RAYGAME_BIG_ENDIAN
static constexpr Endian ENDIANNESS = Endian::BIG;
#    endif
#endif
} // namespace core::config

//=============================================================================
// Compiler Config
//=============================================================================

namespace core::config {
//! Compiler Definitions
enum class Compiler : std::uint8_t {
    CLANG, //!< Clang-based compiler
    GCC,   //!< GCC-based compiler
    MSC,   //!< MSVC-based compiler
    MINGW, //!< MINGW-based compiler
};

#if defined(__clang__)
#    define RAYGAME_CC_CLANG
static constexpr Compiler COMPILER = Compiler::CLANG;
//NOLINTNEXTLINE(*-magic-numbers)
static_assert(__clang_major__ >= 17, "Only tested on clang 17 and higher");
#elif defined(__GNUC__)
#    define RAYGAME_CC_GCC
static constexpr Compiler COMPILER = Compiler::GCC;
// static_assert(false, "Not tested on GCC yet");
#elif defined(__MINGW32__)
#    define RAYGAME_CC_MINGW
static constexpr Compiler COMPILER = Compiler::MINGW;
static_assert(false, "Not tested on MinGW yet");
#elif defined(_MSC_VER)
#    define RAYGAME_CC_MSC
static constexpr Compiler COMPILER = Compiler::MSC;
static_assert(false, "Not tested on MSC yet");
#else
static_assert(false, "Unknown Compiler");
#endif

//! Compiler has GCC-like compiler features
static constexpr bool COMPILER_IS_GCC_LIKE =
    (COMPILER == Compiler::GCC || COMPILER == Compiler::CLANG);
} // namespace core::config

//=============================================================================
// OS Config
//=============================================================================

namespace core::config {
//! Operating System Definitions
#if (__STDC_HOSTED__ == 1)
enum class OperatingSystem : std::uint8_t {
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

#    if defined(__ANDROID__)
#        define RAYGAME_OS_ANDROID
static constexpr OperatingSystem OPERATING_SYSTEM = OperatingSystem::ANDROID;
static_assert(false, "Not tested on Android yet");
#    elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)  \
        || defined(__bsdi__)
#        define RAYGAME_OS_BSD
static constexpr OperatingSystem OPERATING_SYSTEM = OperatingSystem::BSD;
static_assert(false, "Not tested on BSD yet");
#    elif defined(__GNU__) || defined(__gnu_hurd__)
#        define RAYGAME_OS_HURD
#        warning "Imagine using hurd, who are you? Richard Stallman?"
static constexpr OperatingSystem OPERATING_SYSTEM = OperatingSystem::HURD;
static_assert(false, "Not tested on HURD");
#    elif defined(__gnu_linux__) || defined(__linux__)
#        define RAYGAME_OS_LINUX
static constexpr OperatingSystem OPERATING_SYSTEM = OperatingSystem::LINUX;
#    elif defined(__QNX__) || defined(__QNXNTO__)
#        define RAYGAME_OS_QNX
#        warning "Why? Just why?"
#        warning "What possessed you to try running games on QNX?"
static constexpr OperatingSystem OPERATING_SYSTEM = OperatingSystem::QNX;
static_assert(false, "Not tested on QNX");
#    elif defined(macintosh) || defined(Macintosh)                             \
        || (defined(__APPLE__) && defined(__MACH__))
#        define RAYGAME_OS_MAC
static constexpr OperatingSystem OPERATING_SYSTEM = OperatingSystem::MAC;
static_assert(false, "Not tested on Apple Macintosh");
#    elif defined(_WIN64)
#        define RAYGAME_OS_WIN64
#        warning "Imagine using a niche videogame operating system..."
#        warning "Couldn't be me"
static constexpr OperatingSystem OPERATING_SYSTEM = OperatingSystem::WIN64;
static_assert(false, "Not tested on Windows 64-bit yet");
#    elif defined(_WIN32)
#        define RAYGAME_OS_WIN32
#        warning "Imagine using a niche videogame operating system..."
#        warning                                                               \
            "Couldn't be me, but at least the 32-bit versions"                 \
            " generally didn't have as much spyware"
static constexpr OperatingSystem OPERATING_SYSTEM = OperatingSystem::WIN32;
static_assert(false, "Not tested on Windows 32-bit yet");
#    else
static_assert(false, "Unknown Architecture");
#    endif
#else
static_assert(false, "Cannot run without an OS");
#endif
} // namespace core::config

//=============================================================================
// Window Backend Config
//=============================================================================

namespace core::config {
//! Window Backends
enum class GuiBackend : std::uint8_t {
    COCOA,
    DWM,
    TEMPLE,
    WAYLAND,
    X11,
};
} // namespace core::config

//=============================================================================
// Build Type Config
//=============================================================================

namespace core::config {
enum class BuildType : std::uint8_t {
    DEBUG,
    RELEASE,
};

#if defined(NDEBUG)
#    define RAYGAME_BUILD_TYPE_RELEASE
static constexpr BuildType BUILD_TYPE = BuildType::RELEASE;
#else
#    define RAYGAME_BUILD_TYPE_DEBUG
static constexpr BuildType BUILD_TYPE = BuildType::DEBUG;
#endif
} // namespace core::config

//=============================================================================
// SIMD Config
//=============================================================================

namespace core::config {
//! SIMD Feature Definitions
#if defined(__SSE2__)
#    define RAYGAME_HAS_SSE2
#    define RAYGAME_SIMD_128BIT
#    if defined(RAYGAME_HAS_SSE2)
#        if defined(__SSSE3__)
#            define RAYGAME_HAS_SSSE3
#        endif
#        if defined(__AVX__)
#            define RAYGAME_HAS_AVX
#            if defined(RAYGAME_HAS_AVX)
#                define RAYGAME_SIMD_256BIT_F
#                if defined(__AVX2__)
#                    define RAYGAME_HAS_AVX2
#                    define RAYGAME_SIMD_256BIT_X
#                endif
#            endif
#        endif
#    endif
#elif defined(__ARM_NEON)
#    define RAYGAME_HAS_NEON
#    define RAYGAME_SIMD_128BIT
#endif

struct Simd {
    //! SIMD supports SSE2
    static consteval bool sse2() {
#if defined(RAYGAME_HAS_SSE2)
        return true;
#else
        return false;
#endif
    }

    //! SIMD supports SSSE3
    static consteval bool ssse3() {
#if defined(RAYGAME_HAS_SSSE3)
        return true;
#else
        return false;
#endif
    }

    //! SIMD supports AVX
    static consteval bool avx() {
#if defined(RAYGAME_HAS_AVX)
        return true;
#else
        return false;
#endif
    }

    //! SIMD supports AVX2
    static consteval bool avx2() {
#if defined(RAYGAME_HAS_AVX2)
        return true;
#else
        return false;
#endif
    }

    //! SIMD supports 256-bit float operations
    static consteval bool float256() {
#if defined(RAYGAME_HAS_SIMD_256BIT_F)
        return true;
#else
        return false;
#endif
    }

    //! SIMD supports 256-bit integer operations
    static consteval bool x256() {
#if defined(RAYGAME_HAS_SIMD_256BIT_X)
        return true;
#else
        return false;
#endif
    }

    //! SIMD supports ARM NEON
    static consteval bool neon() {
#if defined(RAYGAME_HAS_NEON)
        return true;
#else
        return false;
#endif
    }

    //! SIMD supports 128-bit integer operations
    static consteval bool simd128() {
#if defined(RAYGAME_HAS_SIMD_128BIT)
        return true;
#else
        return false;
#endif
    }
};

//=============================================================================
// Compiler-Dependant Pragma Macros
//=============================================================================
// NOLINTBEGIN(*-macro-usage)

//! @defgroup macros_machine_pragma Pragma macros
//! push, string, pop pragmas for suppressing compiler warnings
//! @{

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

//! @}

// NOLINTEND(*-macro-usage)

} // namespace core::config
