#include "raygame/core/debug.h"
#include "raytest/raytest.h"

class TestClass {};

template<typename T>
class TestClassTemplate {};

RG_TEST(Logger, TypeName) {
    using core::debug::type_name;

    RG_SUBCASE("type_name<T>()") {
        RG_CHECK_EQ(type_name<uint8_t>(), "uint8_t");
        RG_CHECK_EQ(type_name<uint16_t>(), "uint16_t");
        RG_CHECK_EQ(type_name<uint32_t>(), "uint32_t");
        RG_CHECK_EQ(type_name<uint64_t>(), "uint64_t");
        RG_CHECK_EQ(type_name<int8_t>(), "int8_t");
        RG_CHECK_EQ(type_name<int16_t>(), "int16_t");
        RG_CHECK_EQ(type_name<int32_t>(), "int32_t");
        RG_CHECK_EQ(type_name<int64_t>(), "int64_t");
        RG_CHECK_EQ(type_name<int>(), "int32_t");
        RG_CHECK_EQ(type_name<char>(), "char");
        RG_CHECK_EQ(type_name<TestClass>(), "TestClass");
    }

    RG_SUBCASE("type_name(auto val)") {
        const TestClass testclass;
        RG_CHECK_EQ(type_name(uint8_t()), "uint8_t");
        RG_CHECK_EQ(type_name(testclass), "TestClass");
        RG_CHECK_EQ(type_name(1UL), "uint64_t");
    }
}
