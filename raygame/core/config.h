#pragma once
#include <cstddef>
#include <cstdint>

/*!
 *  @defgroup macros_machine Machine-Specific Macros
 *  Macros used to specify machine-specific traits/features
 */

#include "raygame/core/config/feature_check.h" // IWYU pragma: export
#include "raygame/core/config/stringify.h"     // IWYU pragma: export

//=============================================================================
// User-Configurable Macros
//=============================================================================
#include "raygame/core/config/user_defines.h" // IWYU pragma: export

namespace core::config {
//! Game's target FPS
constexpr size_t TARGET_FPS         = RAYGAME_TARGET_FPS;
//! Force generic implementations
constexpr bool   FORCE_GENERIC_IMPL = RAYGAME_FORCE_GENERIC_IMPL;
} // namespace core::config

#if !__has_include(<source_location>)
#    error "source_location unsupported, cannot continue"
#endif

//=============================================================================
// Assertion
//=============================================================================
#include "raygame/core/config/assert.h" // IWYU pragma: export

//=============================================================================
// Architecture Config
//=============================================================================
#include "raygame/core/config/architecture.h" // IWYU pragma: export

namespace core::config {
//! Architecture Definitions
enum class Architecture : std::uint8_t {
    X86_64, //!< X86, 64-Bit
    X86_32, //!< X86, 32-Bit
    ARM,    //!< ARM, 32-Bit
    ARM64,  //!< ARM, 64-Bit
    RISCV,  //!< RISCV
};

constexpr Architecture ARCHITECTURE =
#if defined(RAYGAME_ARCH_X86_64)
    Architecture::X86_64;
#elif defined(RAYGAME_ARCH_X86_32)
    Architecture::X86_32;
#elif defined(RAYGAME_ARCH_RISCV)
    Architecture::RISCV;
#elif defined(RAYGAME_ARCH_ARM64)
    Architecture::ARM64;
#elif defined(RAYGAME_ARCH_ARM)
    Architecture::ARM;
#endif
} // namespace core::config

//=============================================================================
// Endian Config
//=============================================================================
#include "raygame/core/config/endian.h" // IWYU pragma: export

namespace core::config {
//! Endian Definitions
enum class Endian : std::uint8_t {
    LITTLE, //!< Little-Endian
    BIG,    //!< Big-Endian
};

constexpr Endian ENDIANNESS =
#if defined(RAYGAME_LITTLE_ENDIAN)
    Endian::LITTLE;
#elif defined(RAYGAME_BIG_ENDIAN)
    Endian::BIG;
#endif
} // namespace core::config

//=============================================================================
// Compiler Config
//=============================================================================
#include "raygame/core/config/compiler.h" // IWYU pragma: export

namespace core::config {
//! Compiler Definitions
enum class Compiler : std::uint8_t {
    CLANG, //!< Clang-based compiler
    GCC,   //!< GCC-based compiler
    MSC,   //!< MSVC-based compiler
    MINGW, //!< MINGW-based compiler
};

constexpr Compiler COMPILER =
#if defined(RAYGAME_CC_CLANG)
    Compiler::CLANG;
#elif defined(RAYGAME_CC_GCC)
    Compiler::GCC;
#elif defined(RAYGAME_CC_MINGW)
    Compiler::MINGW;
#elif defined(RAYGAME_CC_MSC)
    Compiler::MSC;
#endif

//! Compiler has GCC-like compiler features
constexpr bool COMPILER_IS_GCC_LIKE =
    (COMPILER == Compiler::GCC || COMPILER == Compiler::CLANG);
} // namespace core::config

//=============================================================================
// OS Config
//=============================================================================
#include "raygame/core/config/operating_system.h" // IWYU pragma: export

namespace core::config {
//! Operating System Definitions
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

constexpr OperatingSystem OPERATING_SYSTEM =
#if defined(RAYGAME_OS_ANDROID)
    OperatingSystem::ANDROID;
#elif defined(RAYGAME_OS_BSD)
    OperatingSystem::BSD;
#elif defined(RAYGAME_OS_HURD)
    OperatingSystem::HURD;
#elif defined(RAYGAME_OS_LINUX)
    OperatingSystem::LINUX;
#elif defined(RAYGAME_OS_MAC)
    OperatingSystem::MAC;
#elif defined(RAYGAME_OS_QNX)
    OperatingSystem::QNX;
#elif defined(RAYGAME_OS_TEMPLEOS)
    OperatingSystem::TEMPLEOS;
#elif defined(RAYGAME_OS_WIN32)
    OperatingSystem::WIN32;
#elif defined(RAYGAME_OS_WIN64)
    OperatingSystem::WIN64;
#endif

} // namespace core::config

//=============================================================================
// Window Backend Config
//=============================================================================
#include "raygame/core/config/window_backend.h" // IWYU pragma: export

namespace core::config {
//! Window Backends
enum class GuiBackend : std::uint8_t {
    COCOA,
    DWM,
    TEMPLE,
    WAYLAND,
    X11,
};

class EnabledBackends {
public:
    static constexpr bool cocoa() { return detail::backend_cocoa(); }

    static constexpr bool dwm() { return detail::backend_dwm(); }

    static constexpr bool temple() { return detail::backend_temple(); }

    static constexpr bool wayland() { return detail::backend_wayland(); }

    static constexpr bool x11() { return detail::backend_x11(); }
};
} // namespace core::config

//=============================================================================
// Build Type Config
//=============================================================================
#include "raygame/core/config/build_type.h" // IWYU pragma: export

namespace core::config {
enum class BuildType : std::uint8_t {
    DEBUG,
    RELEASE,
};

constexpr BuildType BUILD_TYPE =
    detail::debug() ? BuildType::DEBUG : BuildType::RELEASE;
} // namespace core::config

//=============================================================================
// SIMD Config
//=============================================================================
#include "raygame/core/config/simd.h" // IWYU pragma: export

namespace core::config {
//! SIMD Feature Definitions
struct Simd {
    //! SIMD supports AVX
    static consteval bool avx() { return detail::has_avx(); }

    //! SIMD supports AVX2
    static consteval bool avx2() { return detail::has_avx2(); }

    //! SIMD supports SSE2
    static consteval bool sse2() { return detail::has_sse2(); }

    //! SIMD supports SSSE3
    static consteval bool ssse3() { return detail::has_ssse3(); }

    //! SIMD supports ARM NEON
    static consteval bool neon() { return detail::has_neon(); }

    //! SIMD supports 128-bit integer operations
    static consteval bool simd128() { return detail::has_simd128(); }

    //! SIMD supports 256-bit float operations
    static consteval bool float256() { return detail::has_float256(); }

    //! SIMD supports 256-bit integer operations
    static consteval bool x256() { return detail::has_x256(); }
};

} // namespace core::config
