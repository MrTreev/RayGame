#pragma once
#include <zppbits.h> // IWYU pragma: keep

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

namespace literals {
using namespace zpp::bits::literals;
} // namespace literals

namespace endian {
using zpp::bits::endian::big;
using zpp::bits::endian::little;
using zpp::bits::endian::native;
using zpp::bits::endian::network;
using zpp::bits::endian::swapped;
} // namespace endian

} // namespace core::serialise
