#pragma once
#include "raygame/core/types.h"

#if defined(__clang__)
#    pragma clang system_header
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Weverything"
#endif

#include "zpp_bits.h" // IWYU pragma: export

#if defined(__clang__)
#    pragma clang diagnostic pop
#endif

namespace core::serialise {

using zpp::bits::access;
using zpp::bits::id;
using zpp::bits::known_id;

using endianness = zpp::bits::endian::big;

template<typename T>
std::vector<byte> serialise(T structured_data) {
    auto [data, in, out] = zpp::bits::data_in_out(endianness{});
    out(structured_data).or_throw();
    return data;
}

template<typename T>
T deserialise(const std::vector<byte>& serial_data) {
    auto [data, in, out] = zpp::bits::data_in_out(endianness{});
    for (const auto& item: serial_data) {
        out(item).or_throw();
    }
    T structured_data;
    in(structured_data).or_throw();
    return structured_data;
}

} // namespace core::serialise
