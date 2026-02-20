#include "raygame/core/serialisation/serialisation.h" // IWYU pragma: keep
#include "raytest/raytest.h"                          // IWYU pragma: keep

struct PublicTest {
    uint32_t m_u32;
    int32_t  m_i32;
    uint16_t m_u16;
    int16_t  m_i16;
};

class PrivateTest {
    friend core::serialise::access;
    uint32_t m_u32;
    int32_t  m_i32;
    uint16_t m_u16;
    int16_t  m_i16;

public:
    PrivateTest() = default;

    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    PrivateTest(uint32_t u32, int32_t i32, uint16_t u16, int16_t i16)
        : m_u32(u32)
        , m_i32(i32)
        , m_u16(u16)
        , m_i16(i16) {}

    [[nodiscard]]
    uint32_t u32() const {
        return m_u32;
    }

    [[nodiscard]]
    int32_t i32() const {
        return m_i32;
    }

    [[nodiscard]]
    uint16_t u16() const {
        return m_u16;
    }

    [[nodiscard]]
    int16_t i16() const {
        return m_i16;
    }
};

RT_TEST(Serialisation, test) {
    RT_SUBCASE("test public") {
        PublicTest test_struct{};
        test_struct.m_u32 = 0x11'11'00'00; // NOLINT(*-magic-numbers)
        test_struct.m_i32 = 0x22'22'33'33; // NOLINT(*-magic-numbers)
        test_struct.m_u16 = 0x15'93;       // NOLINT(*-magic-numbers)
        test_struct.m_i16 = 0x23'51;       // NOLINT(*-magic-numbers)

        const auto testdata = core::serialise::serialise(test_struct);
        auto       out_struct{core::serialise::deserialise<PublicTest>(testdata)};
        RT_CHECK_EQ(test_struct.m_u32, out_struct.m_u32);
        RT_CHECK_EQ(test_struct.m_i32, out_struct.m_i32);
        RT_CHECK_EQ(test_struct.m_u16, out_struct.m_u16);
        RT_CHECK_EQ(test_struct.m_i16, out_struct.m_i16);
    }
    RT_SUBCASE("test private") {
        // NOLINTBEGIN(*-magic-numbers)
        const PrivateTest test_struct{0x11'11'00'00, 0x22'22'33'33, 0x15'93, 0x23'51};
        // NOLINTEND(*-magic-numbers)
        const auto        testdata = core::serialise::serialise(test_struct);
        auto              out_struct{core::serialise::deserialise<PrivateTest>(testdata)};
        RT_CHECK_EQ(test_struct.u32(), out_struct.u32());
        RT_CHECK_EQ(test_struct.i32(), out_struct.i32());
        RT_CHECK_EQ(test_struct.u16(), out_struct.u16());
        RT_CHECK_EQ(test_struct.i16(), out_struct.i16());
    }
}
