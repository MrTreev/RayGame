#if defined(RAYGAME_TESTLIB_DOCTEST)
#    define DOCTEST_CONFIG_IMPLEMENT
#    include <doctest/doctest.h>
#elif defined(RAYGAME_TESTLIB_GTEST)
#    include <gtest/gtest.h>
#else
#    error "No defined test library"
#endif

int main(int argc, char** argv) {
#if defined(RAYGAME_TESTLIB_DOCTEST)
    doctest::Context context{argc, argv};
    return context.run();
#elif defined(RAYGAME_TESTLIB_GTEST)
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif
}
