#include "raygame/core/types.h" // IWYU pragma: keep
#include "raytest/raytest.h"

RG_TEST(Types, Pair) {
    RG_SUBCASE("Return Members") {
        const core::Pair<int16_t> numbers{1, 2};
        EXPECT_EQ(numbers.first(), 1);
        EXPECT_EQ(numbers.second(), 2);
    }

    RG_SUBCASE("Structured binding") {
        const core::Pair<int16_t> numbers{1, 2};
        auto [val1, val2] = numbers;
        EXPECT_EQ(numbers.first(), 1);
        EXPECT_EQ(numbers.second(), 2);
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
        const std::string                   zeros_str{"Pair<uint8_t, uint16_t>(0, 0)"};
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }
}

RG_TEST(Types, Triple) {
    RG_SUBCASE("Return Members") {
        const core::Triple<int16_t> numbers{1, 2, 3};
        EXPECT_EQ(numbers.first(), 1);
        EXPECT_EQ(numbers.second(), 2);
        EXPECT_EQ(numbers.third(), 3);
    }

    RG_SUBCASE("Structured binding") {
        const core::Triple<int16_t> numbers{1, 2, 3};
        auto [val1, val2, val3] = numbers;
        EXPECT_EQ(val1, 1);
        EXPECT_EQ(val2, 2);
        EXPECT_EQ(val3, 3);
    }

    RG_SUBCASE("Single stringify") {
        const core::Triple<uint8_t> zeros{0, 0, 0};
        const std::string           zeros_str{"Triple<uint8_t>(0, 0, 0)"};
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }

    RG_SUBCASE("Full stringify") {
        const core::Triple<uint8_t, uint16_t, uint32_t> zeros{0, 0, 0};
        const std::string zeros_str{"Triple<uint8_t, uint16_t, uint32_t>(0, 0, 0)"};
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }
}

RG_TEST(Types, Quad) {
    RG_SUBCASE("Return Members") {
        const core::Quad<int16_t> smaller{0, 1, 2, 3};
        const core::Quad<int16_t> mid{1, 2, 3, 4};
        const core::Quad<int16_t> bigger{2, 3, 4, 5};
        EXPECT_EQ(smaller, smaller);
        EXPECT_EQ(mid, mid);
        EXPECT_EQ(bigger, bigger);
    }

    RG_SUBCASE("Return Members") {
        const core::Quad<int16_t> numbers{1, 2, 3, 4};
        EXPECT_EQ(numbers.first(), 1);
        EXPECT_EQ(numbers.second(), 2);
        EXPECT_EQ(numbers.third(), 3);
        EXPECT_EQ(numbers.fourth(), 4);
    }

    RG_SUBCASE("Structured binding") {
        const core::Quad<int16_t> numbers{1, 2, 3, 4};
        auto [val1, val2, val3, val4] = numbers;
        EXPECT_EQ(val1, 1);
        EXPECT_EQ(val2, 2);
        EXPECT_EQ(val3, 3);
        EXPECT_EQ(val4, 4);
    }

    RG_SUBCASE("Single stringify") {
        const core::Quad<uint8_t> zeros{0, 0, 0, 0};
        const std::string         zeros_str{"Quad<uint8_t>(0, 0, 0, 0)"};
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }

    RG_SUBCASE("Full stringify") {
        const core::Quad<uint8_t, uint16_t, uint32_t, uint64_t> zeros{0, 0, 0, 0};
        const std::string zeros_str{"Quad<uint8_t, uint16_t, uint32_t, uint64_t>(0, 0, 0, 0)"};
        EXPECT_EQ(std::string(zeros), zeros_str);
        EXPECT_EQ(std::format("{}", zeros), zeros_str);
    }
}
