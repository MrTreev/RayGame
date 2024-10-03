#include "core/math.h" // IWYU pragma: keep

uint64_t core::math::detail::seed = 42;

// Disable global constructor warnings for global random_device, as it is a singleton anyway
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
std::random_device core::math::detail::dev;
#pragma clang diagnostic pop
