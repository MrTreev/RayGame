#pragma once

#define RAYGAME_PP_EQUALS(a, b)          a == b
#define RAYGAME_PP_CONCAT(a, b)          a##b
#define RAYGAME_PP_CONCAT_DEFERRED(a, b) RAYGAME_PP_CONCAT(a, b)

#define RAYGAME_PP_IF_0(true_case, false_case) false_case
#define RAYGAME_PP_IF_1(true_case, false_case) true_case

#define RAYGAME_PP_IF(condition, true_case, false_case)                        \
    RAYGAME_PP_CONCAT_DEFERRED(RAYGAME_PP_IF_, condition)(true_case, false_case)

#define RAYGAME_PP_CASE(condition, true_case)                                  \
    RAYGAME_PP_CONCAT_DEFERRED(RAYGAME_PP_IF_, condition)(true_case, "")

