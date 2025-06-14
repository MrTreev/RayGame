#include "raygame/core/types.h" // IWYU pragma: keep
#include "raytest/raytest.h"
#include <gtest/gtest.h>

RG_TEST(Types, Pair) {
    RG_SUBCASE("Structured binding") {
        const core::Pair<int16_t> numbers{1, 2};
        const auto& [val1, val2] = numbers.get();
        EXPECT_EQ(val1, 1);
        EXPECT_EQ(val2, 2);
    }
    RG_SUBCASE("Single stringify") {
        const core::Pair<uint8_t> zeros{0, 0};
        const std::string         zeros_str{"Pair<uint8_t>(0, 0)"};
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }

    RG_SUBCASE("Full stringify") {
        const core::Pair<uint8_t, uint16_t> zeros{0, 0};
        const std::string zeros_str{"Pair<uint8_t, uint16_t>(0, 0)"};
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }
}

RG_TEST(Types, Triple) {
    RG_SUBCASE("Single stringify") {
        const core::Triple<uint8_t> zeros{0, 0, 0};
        const std::string           zeros_str{"Triple<uint8_t>(0, 0, 0)"};
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }

    RG_SUBCASE("Full stringify") {
        const core::Triple<uint8_t, uint16_t, uint32_t> zeros{0, 0, 0};
        const std::string                               zeros_str{
            "Triple<uint8_t, uint16_t, uint32_t>(0, 0, 0)"
        };
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }
}

RG_TEST(Types, Quad) {
    RG_SUBCASE("Single stringify") {
        const core::Quad<uint8_t> zeros{0, 0, 0, 0};
        const std::string         zeros_str{"Quad<uint8_t>(0, 0, 0, 0)"};
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }

    RG_SUBCASE("Full stringify") {
        const core::Quad<uint8_t, uint16_t, uint32_t, uint64_t>
                          zeros{0, 0, 0, 0};
        const std::string zeros_str{
            "Quad<uint8_t, uint16_t, uint32_t, uint64_t>(0, 0, 0, 0)"
        };
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }
}
