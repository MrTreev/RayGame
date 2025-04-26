#include "raygame/core/condition.h" // IWYU pragma: keep
#include "raygame/core/exception.h"
#include "raytest/tests_begin.h"

RG_TEST_SUITE("core::condition Pre-Tests") {
    using cond_t = core::exception::PreCondition;
    using core::condition::pre_check_max;
    using core::condition::pre_check_min;
    using core::condition::pre_check_range;

    RG_TEST_CASE("Basic checks") {
        using core::condition::pre_condition;
        CHECK_NOTHROW(pre_condition(true, "true"));
        CHECK_THROWS_AS(pre_condition(false, "false"), cond_t);
    }

    RG_TEST_CASE_TEMPLATE("Range checks", T, FWINT_PAIRS) {
        using a_t      = T::A;
        using b_t      = T::B;
        const a_t amin = 1;
        const b_t bmin = 1;
        const a_t aval = 2;
        const b_t bval = 2;
        const a_t amax = 3;
        const b_t bmax = 3;

        RG_SUBCASE("Min Tests") {
            RG_CHECK_NOTHROW(pre_check_min(aval, amin));
            RG_CHECK_NOTHROW(pre_check_min(aval, bmin));
            RG_CHECK_NOTHROW(pre_check_min(bval, amin));
            RG_CHECK_NOTHROW(pre_check_min(bval, bmin));
            RG_CHECK_THROWS_AS(pre_check_min(aval, amax), cond_t);
            RG_CHECK_THROWS_AS(pre_check_min(aval, bmax), cond_t);
            RG_CHECK_THROWS_AS(pre_check_min(bval, amax), cond_t);
            RG_CHECK_THROWS_AS(pre_check_min(bval, bmax), cond_t);
        }

        RG_SUBCASE("Max Tests") {
            RG_CHECK_NOTHROW(pre_check_max(aval, amax));
            RG_CHECK_NOTHROW(pre_check_max(aval, bmax));
            RG_CHECK_NOTHROW(pre_check_max(bval, amax));
            RG_CHECK_NOTHROW(pre_check_max(bval, bmax));
            RG_CHECK_THROWS_AS(pre_check_max(aval, amin), cond_t);
            RG_CHECK_THROWS_AS(pre_check_max(aval, bmin), cond_t);
            RG_CHECK_THROWS_AS(pre_check_max(bval, amin), cond_t);
            RG_CHECK_THROWS_AS(pre_check_max(bval, bmin), cond_t);
        }

        RG_SUBCASE("In-Range Tests") {
            RG_CHECK_NOTHROW(pre_check_range(aval, amin, amax));
            RG_CHECK_NOTHROW(pre_check_range(aval, amin, bmax));
            RG_CHECK_NOTHROW(pre_check_range(aval, bmin, amax));
            RG_CHECK_NOTHROW(pre_check_range(aval, bmin, bmax));
            RG_CHECK_NOTHROW(pre_check_range(bval, amin, amax));
            RG_CHECK_NOTHROW(pre_check_range(bval, amin, bmax));
            RG_CHECK_NOTHROW(pre_check_range(bval, bmin, amax));
            RG_CHECK_NOTHROW(pre_check_range(bval, bmin, bmax));
        }

        RG_SUBCASE("Out-of-Range Tests") {
            // Swapping these is intentional here
            // NOLINTBEGIN(*-suspicious-call-argument)
            RG_CHECK_THROWS_AS(pre_check_range(aval, amax, amin), cond_t);
            RG_CHECK_THROWS_AS(pre_check_range(aval, amax, bmin), cond_t);
            RG_CHECK_THROWS_AS(pre_check_range(aval, bmax, amin), cond_t);
            RG_CHECK_THROWS_AS(pre_check_range(aval, bmax, bmin), cond_t);
            RG_CHECK_THROWS_AS(pre_check_range(bval, amax, amin), cond_t);
            RG_CHECK_THROWS_AS(pre_check_range(bval, amax, bmin), cond_t);
            RG_CHECK_THROWS_AS(pre_check_range(bval, bmax, amin), cond_t);
            RG_CHECK_THROWS_AS(pre_check_range(bval, bmax, bmin), cond_t);
            // NOLINTEND(*-suspicious-call-argument)
        }
    }
}

RG_TEST_SUITE("core::condition::post") {
    using cond_t = core::exception::PostCondition;
    RG_TEST_CASE("Basic checks") {
        using core::condition::post_condition;
        RG_CHECK_NOTHROW(post_condition(true, "true"));
        RG_CHECK_THROWS_AS(post_condition(false, "false"), cond_t);
    }
}

RG_TEST_SUITE("core::condition::check") {
    using cond_t = core::exception::CheckCondition;

    RG_TEST_CASE("Basic checks") {
        using core::condition::check_condition;
        RG_CHECK_NOTHROW(check_condition(true, "true"));
        RG_CHECK_THROWS_AS(check_condition(false, "false"), cond_t);
    }

    RG_TEST_CASE_TEMPLATE("core::condition::check_ptr", T, FWINTS) {
        using core::condition::check_ptr;
        const T* tst_null = nullptr;
        const T  tst_val  = 1;
        const T* tst      = &tst_val;
        RG_CHECK_NOTHROW(check_ptr(tst, "non-null"));
        RG_CHECK_THROWS_AS(check_ptr(tst_null, "null"), cond_t);
    }
}
