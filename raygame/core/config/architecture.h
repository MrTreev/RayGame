#pragma once

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
