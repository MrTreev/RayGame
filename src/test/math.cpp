#include "core/math.h"
#include <limits>
#include <tts/tts.hpp>

#if defined(__clang__)
//#pragma clang diagnostic ignored "-Wc99-extensions"
#endif

#define TEST_LEN 16

using core::exception::Condition;
using core::math::numeric_cast;

#define MINTEST(x)                                                             \
    static_cast<std::intmax_t>(std::numeric_limits<x>::lowest()) - 1
#define MAXTEST(x) static_cast<std::intmax_t>(std::numeric_limits<x>::max()) + 1

TTS_CASE("numeric_cast throws Signed") {
    TTS_THROW(numeric_cast<int8_t>(MINTEST(int8_t)), Condition);
    TTS_THROW(numeric_cast<int8_t>(MAXTEST(int8_t)), Condition);
    TTS_THROW(numeric_cast<int16_t>(MINTEST(int16_t)), Condition);
    TTS_THROW(numeric_cast<int16_t>(MAXTEST(int16_t)), Condition);
    TTS_THROW(numeric_cast<int32_t>(MINTEST(int32_t)), Condition);
    TTS_THROW(numeric_cast<int32_t>(MAXTEST(int32_t)), Condition);
};

#undef MINTEST
#undef MAXTEST

#define MINTEST(x)                                                             \
    static_cast<std::uintmax_t>(std::numeric_limits<x>::lowest()) - 1
#define MAXTEST(x)                                                             \
    static_cast<std::uintmax_t>(std::numeric_limits<x>::max()) + 1

TTS_CASE("numeric_cast throws Unsigned") {
    TTS_THROW(numeric_cast<uint8_t>(MINTEST(uint8_t)), Condition);
    TTS_THROW(numeric_cast<uint8_t>(MAXTEST(uint8_t)), Condition);
    TTS_THROW(numeric_cast<uint16_t>(MINTEST(uint16_t)), Condition);
    TTS_THROW(numeric_cast<uint16_t>(MAXTEST(uint16_t)), Condition);
    TTS_THROW(numeric_cast<uint32_t>(MINTEST(uint32_t)), Condition);
    TTS_THROW(numeric_cast<uint32_t>(MAXTEST(uint32_t)), Condition);
};

#undef MINTEST
#undef MAXTEST

#define MINTEST(x) std::numeric_limits<x>::lowest()
#define MAXTEST(x) std::numeric_limits<x>::max()

TTS_CASE("numeric_cast no_throws") {
    TTS_NO_THROW(numeric_cast<int8_t>(MINTEST(int8_t)));
    TTS_NO_THROW(numeric_cast<int8_t>(MAXTEST(int8_t)));
    TTS_NO_THROW(numeric_cast<int16_t>(MINTEST(int16_t)));
    TTS_NO_THROW(numeric_cast<int16_t>(MAXTEST(int16_t)));
    TTS_NO_THROW(numeric_cast<int32_t>(MINTEST(int32_t)));
    TTS_NO_THROW(numeric_cast<int32_t>(MAXTEST(int32_t)));
    TTS_NO_THROW(numeric_cast<int64_t>(MINTEST(int64_t)));
    TTS_NO_THROW(numeric_cast<int64_t>(MAXTEST(int64_t)));
    TTS_NO_THROW(numeric_cast<uint8_t>(MINTEST(uint8_t)));
    TTS_NO_THROW(numeric_cast<uint8_t>(MAXTEST(uint8_t)));
    TTS_NO_THROW(numeric_cast<uint16_t>(MINTEST(uint16_t)));
    TTS_NO_THROW(numeric_cast<uint16_t>(MAXTEST(uint16_t)));
    TTS_NO_THROW(numeric_cast<uint32_t>(MINTEST(uint32_t)));
    TTS_NO_THROW(numeric_cast<uint32_t>(MAXTEST(uint32_t)));
    TTS_NO_THROW(numeric_cast<uint64_t>(MINTEST(uint64_t)));
};

#undef MINTEST
#undef MAXTEST

TTS_CASE_WITH(
    "numeric_cast uint8_t",
    (std::array<uint8_t, TEST_LEN>),
    tts::generate(tts::between<uint8_t>{
        std::numeric_limits<uint8_t>::lowest(),
        std::numeric_limits<uint8_t>::max()
    })
)

(auto data) {
    for (const auto point: data) {
        TTS_NO_THROW(numeric_cast<uint8_t>(point));
    }
};

TTS_CASE_WITH(
    "numeric_cast int8_t",
    (std::array<int8_t, TEST_LEN>),
    tts::generate(tts::between<int8_t>{
        std::numeric_limits<int8_t>::lowest(),
        std::numeric_limits<int8_t>::max()
    })
)

(auto data) {
    for (const auto point: data) {
        TTS_NO_THROW(numeric_cast<int8_t>(point));
    }
};

TTS_CASE_WITH(
    "numeric_cast uint16_t",
    (std::array<uint16_t, TEST_LEN>),
    tts::generate(tts::between<uint16_t>{
        std::numeric_limits<uint16_t>::lowest(),
        std::numeric_limits<uint16_t>::max()
    })
)

(auto data) {
    for (const auto point: data) {
        TTS_NO_THROW(numeric_cast<uint16_t>(point));
    }
};

TTS_CASE_WITH(
    "numeric_cast int16_t",
    (std::array<int16_t, TEST_LEN>),
    tts::generate(tts::between<int16_t>{
        std::numeric_limits<int16_t>::lowest(),
        std::numeric_limits<int16_t>::max()
    })
)

(auto data) {
    for (const auto point: data) {
        TTS_NO_THROW(numeric_cast<int16_t>(point));
    }
};

TTS_CASE_WITH(
    "numeric_cast uint32_t",
    (std::array<uint32_t, TEST_LEN>),
    tts::generate(tts::between<uint32_t>{
        std::numeric_limits<uint32_t>::lowest(),
        std::numeric_limits<uint32_t>::max()
    })
)

(auto data) {
    for (const auto point: data) {
        TTS_NO_THROW(numeric_cast<uint32_t>(point));
    }
};

TTS_CASE_WITH(
    "numeric_cast int32_t",
    (std::array<int32_t, TEST_LEN>),
    tts::generate(tts::between<int32_t>{
        std::numeric_limits<int32_t>::lowest(),
        std::numeric_limits<int32_t>::max()
    })
)

(auto data) {
    for (const auto point: data) {
        TTS_NO_THROW(numeric_cast<int32_t>(point));
    }
};

TTS_CASE_WITH(
    "numeric_cast uint64_t",
    (std::array<uint64_t, TEST_LEN>),
    tts::generate(tts::between<uint64_t>{
        std::numeric_limits<uint64_t>::lowest(),
        std::numeric_limits<uint64_t>::max()
    })
)

(auto data) {
    for (const auto point: data) {
        TTS_NO_THROW(numeric_cast<uint64_t>(point));
    }
};

TTS_CASE_WITH(
    "numeric_cast int64_t",
    (std::array<int64_t, TEST_LEN>),
    tts::generate(tts::between<int64_t>{
        std::numeric_limits<int64_t>::lowest(),
        std::numeric_limits<int64_t>::max()
    })
)

(auto data) {
    for (const auto point: data) {
        TTS_NO_THROW(numeric_cast<int64_t>(point));
    }
};
