#include "raygame/core/types.h"
#include "raytest/raytest.h"

class TestClass {};

template<typename T>
class TestClassTemplate {};

RT_TEST(Debug, TypeName) {
    using core::debug::type_name;

    RT_SUBCASE("type_name<T>()") {
        RT_CHECK_EQ(type_name<uint8_t>(), "uint8_t");
        RT_CHECK_EQ(type_name<uint16_t>(), "uint16_t");
        RT_CHECK_EQ(type_name<uint32_t>(), "uint32_t");
        RT_CHECK_EQ(type_name<uint64_t>(), "uint64_t");
        RT_CHECK_EQ(type_name<int8_t>(), "int8_t");
        RT_CHECK_EQ(type_name<int16_t>(), "int16_t");
        RT_CHECK_EQ(type_name<int32_t>(), "int32_t");
        RT_CHECK_EQ(type_name<int64_t>(), "int64_t");
        RT_CHECK_EQ(type_name<int>(), "int32_t");
        RT_CHECK_EQ(type_name<char>(), "char");
        RT_CHECK_EQ(type_name<TestClass>(), "TestClass");
    }

    RT_SUBCASE("type_name(auto val)") {
        const TestClass testclass;
        RT_CHECK_EQ(type_name(uint8_t()), "uint8_t");
        RT_CHECK_EQ(type_name(testclass), "TestClass");
        RT_CHECK_EQ(type_name(1UL), "uint64_t");
    }
}

RT_TEST(Debug, LocationMessage) {
    using core::debug::location_message;

    RT_SUBCASE("Location Message") {
        const auto        cur{std::source_location::current()};
        const std::string fna{std::format("debug.cpp:{}", cur.line())};
#if defined(RAYGAME_SOURCE_LOCATION_FULL)
        RT_CHECK_EQ(core::debug::location_message(cur), "tests/core/" + fna);
#elif defined(RAYGAME_SOURCE_LOCATION_BASE)
        RT_CHECK_EQ(core::debug::location_message(cur), fna);
#elif defined(RAYGAME_SOURCE_LOCATION_NONE)
        RT_CHECK_EQ(core::debug::location_message(cur), "");
#endif
    }
}
