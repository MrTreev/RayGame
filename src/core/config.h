#pragma once

// clang-format off
#if (__cplusplus < 202002L)
// clang-format on
static_assert(
    false,
    "This game's code uses features from the C++23 standard, please do not "
    "attempt to compile without support for C++23 features"
);
#    error "This game's code uses features from the C++23 standard"
#    include <THIS_HEADER_SHOULD_NEVER_EXIT> // cause compiler error if prior two attempts don't work
#endif

namespace core {

//! Compiler Definitions
enum class Compiler {
    CLANG,
    GCC,
    MSC,
    MINGW,
};

#if defined(__clang__)
#    define RAYGAME_CC_CLANG
static constexpr Compiler compiler = Compiler::CLANG;
static_assert(__clang_major__ >= 17, "Only tested on clang 17 and higher");
#elif defined(__GNUC__)
#    define RAYGAME_CC_GCC
static constexpr Compiler compiler = Compiler::GCC;
static_assert(__GNUC__ >= 14, "Only tested on GCC 14 and higher");
#elif defined(__MINGW32__)
#    define RAYGAME_CC_MINGW
static constexpr Compiler compiler = Compiler::MINGW;
static_assert(false, "Not tested on MinGW yet");
#elif defined(_MSC_VER)
#    define RAYGAME_CC_MSC
static constexpr Compiler compiler = Compiler::MSC;
static_assert(false, "Not tested on MSC yet");
#else
static_assert(false, "Unknown Compiler");
#endif

// Architecture Definitions
enum class Architecture {
    AMD64,
    X86_64,
    X86_32,
    ARM,
    ARM64,
    RISCV,
};

#if defined(__amd64__) || defined(_M_X64_M_AMD64)
#    define RAYGAME_ARCH_AMD64
static constexpr Architecture architecture = Architecture::AMD64;
#elif defined(__x86_64__) || defined(_M_X64)
#    define RAYGAME_ARCH_X86_64
static constexpr Architecture architecture = Architecture::X86_64;
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
#    define RAYGAME_ARCH_X86_32
static constexpr Architecture architecture = Architecture::X86_32;
#elif defined(__rixscv) || defined(__rixscv_xlen)
#    define RAYGAME_ARCH_RISCV
static constexpr Architecture architecture = Architecture::RISCV;
static_assert(false, "Not tested on RISCV yet");
#elif defined(__aarch64) || defined(_M_ARM64)
#    define RAYGAME_ARCH_ARM64
static constexpr Architecture architecture = Architecture::ARM64;
static_assert(false, "Not tested on ARM64 yet");
#elif defined(__arm__) || defined(_M_ARM)
#    define RAYGAME_ARCH_ARM
static constexpr Architecture architecture = Architecture::ARM;
static_assert(false, "Not tested on ARM yet");
#else
static_assert(false, "Unknown Architecture");
#endif

// Operating System Definitions
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
static constexpr OperatingSystem operatingsystem = OperatingSystem::ANDROID;
static_assert(false, "Not tested on Android yet");
#    elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)  \
        || defined(__bsdi__)
#        define RAYGAME_OS_BSD
static constexpr OperatingSystem operatingsystem = OperatingSystem::BSD;
static_assert(false, "Not tested on BSD yet");
#    elif defined(__CYGWIN__)
#        define RAYGAME_OS_Cygwin
static constexpr OperatingSystem operatingsystem = OperatingSystem::CYGWIN;
static_assert(false, "Not tested on Cygwin yet");
#    elif defined(__GNU__) || defined(__gnu_hurd__)
#        define RAYGAME_OS_HURD
#        warning "Imagine using hurd, who are you? Richard Stallman?"
static constexpr OperatingSystem operatingsystem = OperatingSystem::HURD;
static_assert(false, "Not tested on HURD");
#    elif defined(__gnu_linux__) || defined(__linux__)
#        define RAYGAME_OS_LINUX
static constexpr OperatingSystem operatingsystem = OperatingSystem::LINUX;
#    elif defined(__QNX__) || defined(__QNXNTO__)
#        define RAYGAME_OS_QNX
#        warning "Why? Just why?"
#        warning "What possessed you to try running games on QNX?"
static constexpr OperatingSystem operatingsystem = OperatingSystem::QNX;
static_assert(false, "Not tested on QNX");
#    elif defined(__INTEGRITY)
#        define RAYGAME_OS_INTEGRITY
#        warning "Why? Just why?"
#        warning "What possessed you to try running games on GHS Integrity OS?"
static constexpr OperatingSystem operatingsystem = OperatingSystem::INTEGRITY;
static_assert(false, "Not tested on Integrity");
#    elif defined(macintosh) || defined(Macintosh)                             \
        || (defined(__APPLE__) && defined(__MACH__))
#        define RAYGAME_OS_MAC
static constexpr OperatingSystem operatingsystem = OperatingSystem::MAC;
static_assert(false, "Not tested on Apple Macintosh");
#    elif defined(_WIN64)
#        define RAYGAME_OS_WIN64
#        warning "Imagine using a niche videogame operating system..."
#        warning "Couldn't be me"
static constexpr OperatingSystem operatingsystem = OperatingSystem::WIN64;
static_assert(false, "Not tested on Windows 64-bit yet");
#    elif defined(_WIN32)
#        define RAYGAME_OS_WIN32
#        warning "Imagine using a niche videogame operating system..."
#        warning                                                               \
            "Couldn't be me, but at least the 32-bit versions generally didn't have as much spyware"
static constexpr OperatingSystem operatingsystem = OperatingSystem::WIN32;
static_assert(false, "Not tested on Windows 32-bit yet");
#    else
static_assert(false, "Unknown Architecture");
#    endif
#else
#    error "Cannot run without an OS"
static_assert(false, "Cannot run without an OS");
#endif

#if defined(__SSE2__)
#    define RAYGAME_HAS_SSE2
#    ifdef RAYGAME_HAS_SSE2
#        ifdef __SSSE3__
#            define RAYGAME_HAS_SSE3
#        endif
#        ifdef __AVX__
#            define RAYGAME_HAS_AVX
#            ifdef RAYGAME_HAS_AVX
#                ifdef __AVX2__
#                    define RAYGAME_HAS_AVX2
#                endif
#            endif
#        endif
#    endif
#elif defined(__ARM_NEON)
#    define RAYGAME_HAS_NEON
#endif

enum class Backend {
    RAYLIB,
    DFPSR,
    SFML,
};
#if defined(RAYGAME_BACKEND_RAYLIB)
static constexpr Backend backend = Backend::RAYLIB;
#elif defined(RAYGAME_BACKEND_DFPSR)
static constexpr Backend backend = Backend::DFPSR;
#elif defined(RAYGAME_BACKEND_SFML)
static constexpr Backend backend = Backend::SFML;
#endif

} // namespace core

#if defined(RAYGAME_LOG_LOCATION)
#    if __has_include(<experimental/source_location>)
#        include <experimental/source_location>

namespace core::detail {
using std::experimental::source_location;
}
#    elif __has_include(<source_location>)
#        include <source_location>

namespace core::detail {
using std::source_location;
}
#    else
#        warn "source_location unsupported, disabling RAYGAME_LOG_LOCATION"
#        undef RAYGAME_LOG_LOCATION
#    endif
#endif

#if defined(RAYGAME_LOG_LOCATION)
#    include <string_view>

namespace core::detail {
constexpr std::size_t get_prefix_len(
    const core::detail::source_location loc =
        core::detail::source_location::current()
) {
    const std::string_view search_str = "/src/";
    const std::string_view locname    = loc.file_name();
    const std::size_t      nopref_len = locname.rfind(search_str);
    return nopref_len + search_str.length();
}

constexpr size_t path_count = core::detail::get_prefix_len();

} // namespace core::detail

#endif

#if defined(RAYGAME_CC_CLANG)
#    define RAYGAME_SYSTEM_HEADER _Pragma("clang system_header")
#elif defined(RAYGAME_CC_GCC)
#    define RAYGAME_SYSTEM_HEADER _Pragma("GCC system_header")
#else
#    define RAYGAME_SYSTEM_HEADER
#endif // defined (RAYGAME_CC_CLANG)
