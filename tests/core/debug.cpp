#include "raygame/core/debug.h"
#include "raygame/core/test/tests_begin.h"

class TestClass {};

TEST_SUITE("core::debug::type_name") {
    using core::debug::type_name;
    TEST_CASE("type_name<T>()") {
        const std::string uint8_name     = type_name<uint8_t>();
        const std::string uint16_name    = type_name<uint16_t>();
        const std::string uint32_name    = type_name<uint32_t>();
        const std::string uint64_name    = type_name<uint64_t>();
        const std::string int8_name      = type_name<int8_t>();
        const std::string int16_name     = type_name<int16_t>();
        const std::string int32_name     = type_name<int32_t>();
        const std::string int64_name     = type_name<int64_t>();
        const std::string int_name       = type_name<int>();
        const std::string char_name      = type_name<char>();
        const std::string testclass_name = type_name<TestClass>();
        CHECK_EQ(uint8_name, "uint8_t");
        CHECK_EQ(uint16_name, "uint16_t");
        CHECK_EQ(uint32_name, "uint32_t");
        CHECK_EQ(uint64_name, "uint64_t");
        CHECK_EQ(int8_name, "int8_t");
        CHECK_EQ(int16_name, "int16_t");
        CHECK_EQ(int32_name, "int32_t");
        CHECK_EQ(int64_name, "int64_t");
        CHECK_EQ(int_name, "int32_t");
        CHECK_EQ(char_name, "char");
        CHECK_EQ(testclass_name, "TestClass");
    }
    TEST_CASE("type_name(auto val)") {
        const TestClass   testclass;
        const std::string uint8_name      = type_name(uint8_t());
        const std::string testclass_name  = type_name(testclass);
        const std::string ul_literal_name = type_name(1UL);
        CHECK_EQ(uint8_name, "uint8_t");
        CHECK_EQ(testclass_name, "TestClass");
        CHECK_EQ(ul_literal_name, "uint64_t");
    }
}
