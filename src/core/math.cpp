#include "core/math.h" // IWYU pragma: keep

uint64_t           core::math::detail::seed = 42;
std::random_device core::math::detail::dev;
#if defined(__cpp_lib_philox_engine)
#endif
