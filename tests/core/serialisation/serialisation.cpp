#include "raygame/core/serialisation/serialisation.h" // IWYU pragma: keep
#include "raytest/raytest.h"                          // IWYU pragma: keep
#include <utility>

template<typename T>
class Serialisation: public ::testing::Test {
public:
    T val() { return 1; }
};

RG_TYPED_TEST_SUITE(Serialisation, test::types::All);

RG_TEST(Serialisation, test) {
    RG_SUBCASE("test") {}
}
