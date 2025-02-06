#pragma once

/*!
 *  @defgroup macros_config Configuration Macros
 *  User-defined configuration macros
 */

#if !defined(RAYGAME_FORCE_GENERIC_IMPL)
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
//! @}
