#pragma once

// clang-format off
#if (__cplusplus < 202002L)
static_assert(
    false,
    "This game's code uses features from the C++23 standard, please do not "
    "attempt to compile without support for C++23 features"
);
#endif

#if __has_include(<experimental/source_location>)
#    include <experimental/source_location>
namespace core::detail {
using std::experimental::source_location;
}
#elif __has_include(<source_location>)
#    include <source_location>
namespace core::detail {
using std::source_location;
}
#else
#    error "source_location unsupported, cannot continue"
#endif
// clang-format on

namespace core::config {

//! Force generic implementations of operations
/*!
 * Used for Testing, ignores compiler-specific implementations
 */
#if defined(RAYGAME_FORCE_GENERIC_IMPL)
static constexpr bool FORCE_GENERIC_IMPL = true;
#else
static constexpr bool FORCE_GENERIC_IMPL = false;
#endif

//! Architecture Definitions
enum class Architecture {
    X86_64,
    X86_32,
    ARM,
    ARM64,
    RISCV,
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

//! Compiler Definitions
enum class Endian {
    LITTLE,
    BIG,
    LITTLE_BYTE,
    BIG_BYTE,
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

//! Compiler Definitions
enum class Compiler {
    CLANG,
    GCC,
    MSC,
    MINGW,
};

#if defined(__clang__)
#    define RAYGAME_CC_CLANG
static constexpr Compiler COMPILER = Compiler::CLANG;
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

//! Operating System Definitions
#if (__STDC_HOSTED__ == 1)
enum class OperatingSystem {
    ANDROID,
    BSD,
    CYGWIN,
    HURD,
    LINUX,
    INTEGRITY,
    MAC,
    QNX,
    WIN64,
    WIN32,
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
#    elif defined(__CYGWIN__)
#        define RAYGAME_OS_Cygwin
static constexpr OperatingSystem OPERATING_SYSTEM = OperatingSystem::CYGWIN;
static_assert(false, "Not tested on Cygwin yet");
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
#    elif defined(__INTEGRITY)
#        define RAYGAME_OS_INTEGRITY
#        warning "Why? Just why?"
#        warning "What possessed you to try running games on GHS Integrity OS?"
static constexpr OperatingSystem OPERATING_SYSTEM = OperatingSystem::INTEGRITY;
static_assert(false, "Not tested on Integrity");
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

//! Window System Definitions
enum class WindowBackend {
    WAYLAND,
    X11,
    DWM,
    COCOA,
};

enum class BuildType {
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

//! Compiler has GCC-like compiler features
static constexpr bool COMPILER_IS_GCC_LIKE =
    (COMPILER == Compiler::GCC || COMPILER == Compiler::CLANG);

#if defined(RAYGAME_CC_CLANG)
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

#if defined(RAYGAME_CC_GCC)
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

#if defined(RAYGAME_CC_MSC)
#    define RAYGAME_MSC_SUPPRESS_WARNING_PUSH     __pragma(warning(push))
#    define RAYGAME_MSC_SUPPRESS_WARNING(warnstr) __pragma(warning(disable : w))
#    define RAYGAME_MSC_SUPPRESS_WARNING_POP      __pragma(warning(pop))
#else
#    define RAYGAME_MSC_SUPPRESS_WARNING_PUSH
#    define RAYGAME_MSC_SUPPRESS_WARNING(warnstr)
#    define RAYGAME_MSC_SUPPRESS_WARNING_POP
#endif

#if defined(RAYGAME_BUILD_TYPE_DEBUG)
#    include <cassert>
#    define RAYGAME_UNREACHABLE                                                \
        assert(false && "Reached block marked unreachable")
#else
#    define RAYGAME_UNREACHABLE std::unreachable()
#endif

} // namespace core::config