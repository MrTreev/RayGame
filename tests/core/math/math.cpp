#include "raygame/core/math/math.h"
#include "raytest/raytest.h"

RT_TEST(Deg2Rad, Basic) {
    using core::math::deg2rad;
    using core::math::constants::PI;
    // NOLINTBEGIN(*-magic-numbers)
    RT_TEST_FLOAT(deg2rad(0.F), 0.F);
    RT_TEST_FLOAT(deg2rad(30.F), PI / 6.F);
    RT_TEST_FLOAT(deg2rad(45.F), PI / 4.F);
    RT_TEST_FLOAT(deg2rad(90.F), PI / 2.F);
    RT_TEST_FLOAT(deg2rad(120.F), (2 * PI) / 3.F);
    RT_TEST_FLOAT(deg2rad(150.F), (5 * PI) / 6.F);
    RT_TEST_FLOAT(deg2rad(180.F), PI);
    RT_TEST_FLOAT(deg2rad(210.F), (7 * PI) / 6);
    RT_TEST_FLOAT(deg2rad(270.F), (3 * PI) / 2);
    RT_TEST_FLOAT(deg2rad(360.F), 2 * PI);
    // NOLINTEND(*-magic-numbers)
}

RT_TEST(Rad2Deg, Basic) {
    using core::math::rad2deg;
    using core::math::constants::PI;
    // NOLINTBEGIN(*-magic-numbers)
    RT_TEST_FLOAT(rad2deg(0.F), 0.F);
    RT_TEST_FLOAT(rad2deg(PI / 6.F), 30.F);
    RT_TEST_FLOAT(rad2deg(PI / 4.F), 45.F);
    RT_TEST_FLOAT(rad2deg(PI / 2.F), 90.F);
    RT_TEST_FLOAT(rad2deg((2 * PI) / 3.F), 120.F);
    RT_TEST_FLOAT(rad2deg((5 * PI) / 6.F), 150.F);
    RT_TEST_FLOAT(rad2deg(PI), 180.F);
    RT_TEST_FLOAT(rad2deg((7 * PI) / 6), 210.F);
    RT_TEST_FLOAT(rad2deg((3 * PI) / 2), 270.F);
    RT_TEST_FLOAT(rad2deg(2 * PI), 360.F);
    // NOLINTEND(*-magic-numbers)
}
