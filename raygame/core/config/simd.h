#pragma once

namespace core::config::detail {
consteval bool has_sse2() {
#if defined(__SSE2__)
    return true;
#else
    return false;
#endif
}

consteval bool has_avx() {
#if defined(__AVX__)
    return true;
#else
    return false;
#endif
}

consteval bool has_avx2() {
#if defined(__AVX2__)
    return true;
#else
    return false;
#endif
}

consteval bool has_ssse3() {
#if defined(__SSSE3__)
    return true;
#else
    return false;
#endif
}

consteval bool has_neon() {
#if defined(__ARM_NEON)
    return true;
#else
    return false;
#endif
}

consteval bool has_simd128() {
#if defined(RAYGAME_HAS_NEON) || defined(RAYGAME_HAS_SSE2)
    return true;
#else
    return false;
#endif
}

consteval bool has_float256() {
#if defined(RAYGAME_HAS_AVX)
    return true;
#else
    return false;
#endif
}

consteval bool has_x256() {
#if defined(RAYGAME_HAS_AVX2)
    return true;
#else
    return false;
#endif
}

} // namespace core::config::detail
