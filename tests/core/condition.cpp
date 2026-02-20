#include "raygame/core/condition.h" // IWYU pragma: keep
#include "raygame/core/exception.h"
#include "raytest/raytest.h"

namespace {
template<typename T>
class ConditionTest: public ::testing::Test {
public:
    ConditionTest()                                = default;
    ConditionTest(const ConditionTest&)            = delete;
    ConditionTest(ConditionTest&&)                 = delete;
    ConditionTest& operator=(const ConditionTest&) = delete;
    ConditionTest& operator=(ConditionTest&&)      = delete;
    ~ConditionTest() override                      = default;

    void SetUp() override {}

    void TearDown() override {}

    T::A amin() { return 1; }

    T::B bmin() { return 1; }

    T::A aval() { return 2; }

    T::B bval() { return 2; }

    T::A amax() { return 3; }

    T::B bmax() { return 3; }
};

RT_TYPED_TEST_SUITE(ConditionTest, test::types::IntegralPairs);

RT_TYPED_TEST(ConditionTest, Basics) {
    using cond_t = core::exception::PreCondition;
    RT_SUBCASE("Min Tests") {
        using core::condition::pre_check_min;
        RT_CHECK_NO_THROW(pre_check_min(this->aval(), this->amin()));
        RT_CHECK_NO_THROW(pre_check_min(this->aval(), this->bmin()));
        RT_CHECK_NO_THROW(pre_check_min(this->bval(), this->amin()));
        RT_CHECK_NO_THROW(pre_check_min(this->bval(), this->bmin()));
        RT_CHECK_THROW(pre_check_min(this->aval(), this->amax()), cond_t);
        RT_CHECK_THROW(pre_check_min(this->aval(), this->bmax()), cond_t);
        RT_CHECK_THROW(pre_check_min(this->bval(), this->amax()), cond_t);
        RT_CHECK_THROW(pre_check_min(this->bval(), this->bmax()), cond_t);
    }

    RT_SUBCASE("Max Tests") {
        using core::condition::pre_check_max;
        RT_CHECK_NO_THROW(pre_check_max(this->aval(), this->amax()));
        RT_CHECK_NO_THROW(pre_check_max(this->aval(), this->bmax()));
        RT_CHECK_NO_THROW(pre_check_max(this->bval(), this->amax()));
        RT_CHECK_NO_THROW(pre_check_max(this->bval(), this->bmax()));
        RT_CHECK_THROW(pre_check_max(this->aval(), this->amin()), cond_t);
        RT_CHECK_THROW(pre_check_max(this->aval(), this->bmin()), cond_t);
        RT_CHECK_THROW(pre_check_max(this->bval(), this->amin()), cond_t);
        RT_CHECK_THROW(pre_check_max(this->bval(), this->bmin()), cond_t);
    }

    RT_SUBCASE("In-Range Tests") {
        using core::condition::pre_check_range;
#define CRTHIS(i, j, k) pre_check_range(this->i##val(), this->j##min(), this->k##max())
        RT_CHECK_NO_THROW(CRTHIS(a, a, a));
        RT_CHECK_NO_THROW(CRTHIS(a, a, b));
        RT_CHECK_NO_THROW(CRTHIS(a, b, a));
        RT_CHECK_NO_THROW(CRTHIS(a, b, b));
        RT_CHECK_NO_THROW(CRTHIS(b, a, a));
        RT_CHECK_NO_THROW(CRTHIS(b, a, b));
        RT_CHECK_NO_THROW(CRTHIS(b, b, a));
        RT_CHECK_NO_THROW(CRTHIS(b, b, b));
#undef CRTHIS
    }

    RT_SUBCASE("Out-of-Range Tests") {
        using core::condition::pre_check_range;
        // Swapping these is intentional here
        // NOLINTBEGIN(*-suspicious-call-argument)
#define CRTHIS(i, j, k) pre_check_range(this->i##val(), this->j##max(), this->k##min())
        RT_CHECK_THROW(CRTHIS(a, a, a), cond_t);
        RT_CHECK_THROW(CRTHIS(a, a, b), cond_t);
        RT_CHECK_THROW(CRTHIS(a, b, a), cond_t);
        RT_CHECK_THROW(CRTHIS(a, b, b), cond_t);
        RT_CHECK_THROW(CRTHIS(b, a, a), cond_t);
        RT_CHECK_THROW(CRTHIS(b, a, b), cond_t);
        RT_CHECK_THROW(CRTHIS(b, b, a), cond_t);
        RT_CHECK_THROW(CRTHIS(b, b, b), cond_t);
#undef CRTHIS
        // NOLINTEND(*-suspicious-call-argument)
    }
}

RT_TEST(Condition, Post) {
    using cond_t = core::exception::PostCondition;
    using core::condition::post_condition;
    RT_CHECK_NO_THROW(post_condition(true, "true"));
    RT_CHECK_THROW(post_condition(false, "false"), cond_t);
}

RT_TEST(Condition, Checks) {
    using cond_t = core::exception::CheckCondition;

    RT_SUBCASE("Basic checks") {
        using core::condition::check_condition;
        RT_CHECK_NO_THROW(check_condition(true, "true"));
        RT_CHECK_THROW(check_condition(false, "false"), cond_t);
    }

    RT_SUBCASE("core::condition::check_ptr") {
        using core::condition::check_ptr;
        const int* tst_null = nullptr;
        const int  tst_val  = 1;
        const int* tst      = &tst_val;
        RT_CHECK_NO_THROW(check_ptr(tst, "non-null"));
        RT_CHECK_THROW(check_ptr(tst_null, "null"), cond_t);
    }
}

} // namespace
