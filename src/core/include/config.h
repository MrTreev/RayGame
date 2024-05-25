#pragma once

#if (__cplusplus < 202'002L)
static_assert(
    false,
    "This game's code uses features from the C++23 standard, please do not "
    "attempt to compile without support for C++23 features"
);
#endif

namespace core::config {

// Compiler Definitions
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
#elif defined(_MSC_VER)
#    define RAYGAME_CC_MSC
static constexpr Compiler compiler = Compiler::MSC;
static_assert(false, "Not tested on MSC yet");
#elif defined(__MINGW32__)
#    define RAYGAME_CC_MINGW
static constexpr Compiler compiler = Compiler::MINGW;
static_assert(false, "Not tested on MinGW yet");
#else
static_assert(false, "Unknown Compiler");
#endif

// Architecture Definitions
enum class Architecture {
    AMD64,
    X86_64,
    ARM,
    ARM64,
    RISCV,
};
#if defined(__amd64__) || defined(_M_X64_M_AMD64)
#    define RAYGAME_ARCH_AMD64
#elif defined(i386__) || defined(__i386) || defined(_X86_)
#    define RAYGAME_ARCH_X86
#elif defined(__arm__) || defined(_M_ARM)
#    define RAYGAME_ARCH_ARM
static_assert(false, "Not tested on ARM yet");
#elif defined(__rixscv) || defined(__rixscv_xlen)
#    define RAYGAME_ARCH_RISCV
static_assert(false, "Not tested on RISCV yet");
#elif defined(__aarch64) || defined(_M_ARM64)
#    define RAYGAME_ARCH_ARM64
static_assert(false, "Not tested on ARM64 yet");
#else
static_assert(false, "Unknown Architecture");
#endif

} // namespace core::config
