#pragma once
#if defined(__clang__)
#    pragma clang system_header
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Weverything"
#endif

#include <zpp_bits.h> // IWYU pragma: export

#if defined(__clang__)
#    pragma GCC diagnostic pop
#endif

namespace core::serialise {

using zpp::bits::access;
using zpp::bits::id;
using zpp::bits::known_id;

using zpp::bits::in;
using zpp::bits::in_out;
using zpp::bits::out;

using zpp::bits::data_in;
using zpp::bits::data_in_out;
using zpp::bits::data_out;

} // namespace core::serialise
