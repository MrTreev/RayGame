#pragma once
#include "raygame/core/types.h"
#include <limits>
#include <vector>

namespace core::math {

//! Returns a random value in a range
/*!
 * @param min minimum random value
 * @param max maximum random value
 * @return random value in range
 *
 * @pre min < max
 */
template<typename T>
requires std::is_integral_v<T> && std::is_trivial_v<T>
T rand(
    T min = std::numeric_limits<T>::min(),
    T max = std::numeric_limits<T>::max()
);

extern template uint8_t  rand(uint8_t min, uint8_t max);
extern template uint16_t rand(uint16_t min, uint16_t max);
extern template uint32_t rand(uint32_t min, uint32_t max);
extern template uint64_t rand(uint64_t min, uint64_t max);
extern template int8_t   rand(int8_t min, int8_t max);
extern template int16_t  rand(int16_t min, int16_t max);
extern template int32_t  rand(int32_t min, int32_t max);
extern template int64_t  rand(int64_t min, int64_t max);

//! Returns a vector of N random values in a range
/*!
 * @param amount number of elements
 * @param min minimum random value
 * @param max maximum random value
 * @return vector of N random values in range
 *
 * @pre min < max
 */
template<typename T>
requires std::is_integral_v<T> && std::is_trivial_v<T>
std::vector<T> rand_n(
    size_t amount,
    T      min = std::numeric_limits<T>::min(),
    T      max = std::numeric_limits<T>::max()
);

extern template std::vector<uint8_t>
rand_n(size_t amount, uint8_t min, uint8_t max);
extern template std::vector<uint16_t>
rand_n(size_t amount, uint16_t min, uint16_t max);
extern template std::vector<uint32_t>
rand_n(size_t amount, uint32_t min, uint32_t max);
extern template std::vector<uint64_t>
rand_n(size_t amount, uint64_t min, uint64_t max);
extern template std::vector<int8_t>
rand_n(size_t amount, int8_t min, int8_t max);
extern template std::vector<int16_t>
rand_n(size_t amount, int16_t min, int16_t max);
extern template std::vector<int32_t>
rand_n(size_t amount, int32_t min, int32_t max);
extern template std::vector<int64_t>
rand_n(size_t amount, int64_t min, int64_t max);

} // namespace core::math
