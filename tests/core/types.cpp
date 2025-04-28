#include "raygame/core/types.h" // IWYU pragma: keep
#include "raytest/raytest.h"

RG_TEST(Types, Pair) {
    RG_SUBCASE("Single stringify") {
        const core::Pair<uint8_t> zeros = {.a = 0, .b = 0};
        const std::string         zeros_str{"Pair<uint8_t>(a: 0, b: 0)"};
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }

    RG_SUBCASE("Full stringify") {
        const core::Pair<uint8_t, uint16_t> zeros = {.a = 0, .b = 0};
        const std::string zeros_str{"Pair<uint8_t, uint16_t>(a: 0, b: 0)"};
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }
}

RG_TEST(Types, Triple) {
    RG_SUBCASE("Single stringify") {
        const core::Triple<uint8_t> zeros = {.a = 0, .b = 0, .c = 0};
        const std::string zeros_str{"Triple<uint8_t>(a: 0, b: 0, c: 0)"};
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }

    RG_SUBCASE("Full stringify") {
        const core::Triple<uint8_t, uint16_t, uint32_t> zeros =
            {.a = 0, .b = 0, .c = 0};
        const std::string zeros_str{
            "Triple<uint8_t, uint16_t, uint32_t>(a: 0, b: 0, c: 0)"
        };
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }
}

RG_TEST(Types, Quad) {
    RG_SUBCASE("Single stringify") {
        const core::Quad<uint8_t> zeros = {.a = 0, .b = 0, .c = 0, .d = 0};
        const std::string zeros_str{"Quad<uint8_t>(a: 0, b: 0, c: 0, d: 0)"};
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }

    RG_SUBCASE("Full stringify") {
        const core::Quad<uint8_t, uint16_t, uint32_t, uint64_t> zeros =
            {.a = 0, .b = 0, .c = 0, .d = 0};
        const std::string zeros_str{
            "Quad<uint8_t, uint16_t, uint32_t, uint64_t>"
            "(a: 0, b: 0, c: 0, d: 0)"
        };
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }
}
