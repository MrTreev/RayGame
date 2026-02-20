#include "raygame/core/types.h" // IWYU pragma: keep
#include "raytest/raytest.h"

RT_TEST(Types, Pair) {
    RT_SUBCASE("Return Members") {
        const core::Pair<int16_t> numbers{1, 2};
        RT_CHECK_EQ(numbers.first(), 1);
        RT_CHECK_EQ(numbers.second(), 2);
    }

    RT_SUBCASE("Structured binding") {
        const core::Pair<int16_t> numbers{1, 2};
        auto [val1, val2] = numbers;
        RT_CHECK_EQ(numbers.first(), 1);
        RT_CHECK_EQ(numbers.second(), 2);
        RT_CHECK_EQ(val1, 1);
        RT_CHECK_EQ(val2, 2);
    }
    RT_SUBCASE("Single stringify") {
        const core::Pair<uint8_t> zeros{0, 0};
        const std::string         zeros_str{"Pair<uint8_t>(0, 0)"};
        RT_CHECK_EQ(std::string(zeros), zeros_str);
        RT_CHECK_EQ(std::format("{}", zeros), zeros_str);
    }

    RT_SUBCASE("Full stringify") {
        const core::Pair<uint8_t, uint16_t> zeros{0, 0};
        const std::string                   zeros_str{"Pair<uint8_t, uint16_t>(0, 0)"};
        RT_CHECK_EQ(std::string(zeros), zeros_str);
        RT_CHECK_EQ(std::format("{}", zeros), zeros_str);
    }
}

RT_TEST(Types, Triple) {
    RT_SUBCASE("Return Members") {
        const core::Triple<int16_t> numbers{1, 2, 3};
        RT_CHECK_EQ(numbers.first(), 1);
        RT_CHECK_EQ(numbers.second(), 2);
        RT_CHECK_EQ(numbers.third(), 3);
    }

    RT_SUBCASE("Structured binding") {
        const core::Triple<int16_t> numbers{1, 2, 3};
        auto [val1, val2, val3] = numbers;
        RT_CHECK_EQ(val1, 1);
        RT_CHECK_EQ(val2, 2);
        RT_CHECK_EQ(val3, 3);
    }

    RT_SUBCASE("Single stringify") {
        const core::Triple<uint8_t> zeros{0, 0, 0};
        const std::string           zeros_str{"Triple<uint8_t>(0, 0, 0)"};
        RT_CHECK_EQ(std::string(zeros), zeros_str);
        RT_CHECK_EQ(std::format("{}", zeros), zeros_str);
    }

    RT_SUBCASE("Full stringify") {
        const core::Triple<uint8_t, uint16_t, uint32_t> zeros{0, 0, 0};
        const std::string zeros_str{"Triple<uint8_t, uint16_t, uint32_t>(0, 0, 0)"};
        RT_CHECK_EQ(std::string(zeros), zeros_str);
        RT_CHECK_EQ(std::format("{}", zeros), zeros_str);
    }
}

RT_TEST(Types, Quad) {
    RT_SUBCASE("Return Members") {
        const core::Quad<int16_t> smaller{0, 1, 2, 3};
        const core::Quad<int16_t> mid{1, 2, 3, 4};
        const core::Quad<int16_t> bigger{2, 3, 4, 5};
        RT_CHECK_EQ(smaller, smaller);
        RT_CHECK_EQ(mid, mid);
        RT_CHECK_EQ(bigger, bigger);
    }

    RT_SUBCASE("Return Members") {
        const core::Quad<int16_t> numbers{1, 2, 3, 4};
        RT_CHECK_EQ(numbers.first(), 1);
        RT_CHECK_EQ(numbers.second(), 2);
        RT_CHECK_EQ(numbers.third(), 3);
        RT_CHECK_EQ(numbers.fourth(), 4);
    }

    RT_SUBCASE("Structured binding") {
        const core::Quad<int16_t> numbers{1, 2, 3, 4};
        auto [val1, val2, val3, val4] = numbers;
        RT_CHECK_EQ(val1, 1);
        RT_CHECK_EQ(val2, 2);
        RT_CHECK_EQ(val3, 3);
        RT_CHECK_EQ(val4, 4);
    }

    RT_SUBCASE("Single stringify") {
        const core::Quad<uint8_t> zeros{0, 0, 0, 0};
        const std::string         zeros_str{"Quad<uint8_t>(0, 0, 0, 0)"};
        RT_CHECK_EQ(std::string(zeros), zeros_str);
        RT_CHECK_EQ(std::format("{}", zeros), zeros_str);
    }

    RT_SUBCASE("Full stringify") {
        const core::Quad<uint8_t, uint16_t, uint32_t, uint64_t> zeros{0, 0, 0, 0};
        const std::string zeros_str{"Quad<uint8_t, uint16_t, uint32_t, uint64_t>(0, 0, 0, 0)"};
        RT_CHECK_EQ(std::string(zeros), zeros_str);
        RT_CHECK_EQ(std::format("{}", zeros), zeros_str);
    }
}
