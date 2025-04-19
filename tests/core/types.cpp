#include "raytest/tests_begin.h"
#include "raygame/core/types.h" // IWYU pragma: keep

TEST_SUITE("core::Pair") {
    TEST_CASE("String functions") {
        {
            const core::Pair<uint8_t> zeros = {.a = 0, .b = 0};
            const std::string         zeros_str{"Pair<uint8_t>(a: 0, b: 0)"};
            CHECK_EQ(std::string(zeros), zeros_str);
            CHECK_EQ(std::format("{}", zeros), zeros_str);
        }

        {
            const core::Pair<uint8_t, uint16_t> zeros = {.a = 0, .b = 0};
            const std::string zeros_str{"Pair<uint8_t, uint16_t>(a: 0, b: 0)"};
            CHECK_EQ(std::string(zeros), zeros_str);
            CHECK_EQ(std::format("{}", zeros), zeros_str);
        }
    }
}

TEST_SUITE("core::Triple") {
    TEST_CASE("String functions") {
        {
            const core::Triple<uint8_t> zeros = {.a = 0, .b = 0, .c = 0};
            const std::string zeros_str{"Triple<uint8_t>(a: 0, b: 0, c: 0)"};
            CHECK_EQ(std::string(zeros), zeros_str);
            CHECK_EQ(std::format("{}", zeros), zeros_str);
        }

        {
            const core::Triple<uint8_t, uint16_t, uint32_t> zeros =
                {.a = 0, .b = 0, .c = 0};
            const std::string zeros_str{
                "Triple<uint8_t, uint16_t, uint32_t>(a: 0, b: 0, c: 0)"
            };
            CHECK_EQ(std::string(zeros), zeros_str);
            CHECK_EQ(std::format("{}", zeros), zeros_str);
        }
    }
}

TEST_SUITE("core::Quad") {
    TEST_CASE("String functions") {
        {
            const core::Quad<uint8_t> zeros = {.a = 0, .b = 0, .c = 0, .d = 0};
            const std::string zeros_str{"Quad<uint8_t>(a: 0, b: 0, c: 0, d: 0)"
            };
            CHECK_EQ(std::string(zeros), zeros_str);
            CHECK_EQ(std::format("{}", zeros), zeros_str);
        }

        {
            const core::Quad<uint8_t, uint16_t, uint32_t, uint64_t> zeros =
                {.a = 0, .b = 0, .c = 0, .d = 0};
            const std::string zeros_str{
                "Quad<uint8_t, uint16_t, uint32_t, uint64_t>"
                "(a: 0, b: 0, c: 0, d: 0)"
            };
            CHECK_EQ(std::string(zeros), zeros_str);
            CHECK_EQ(std::format("{}", zeros), zeros_str);
        }
    }
}
