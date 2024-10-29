raygame_core_lib(
    Math
    SOURCES
    arithmetic.cpp
    arithmetic/safe_add.cpp
    arithmetic/safe_div.cpp
    arithmetic/safe_mult.cpp
    arithmetic/safe_sub.cpp
    math.cpp
    mathrule.cpp
    numeric_cast.cpp
    random.cpp
    rect.cpp
    vector.cpp
    HEADERS
    arithmetic.h
    arithmetic/safe_add.h
    arithmetic/safe_div.h
    arithmetic/safe_mult.h
    arithmetic/safe_sub.h
    math.h
    mathrule.h
    numeric_cast.h
    random.h
    rect.h
    vector.h
    PUBLIC_DEPENDS
    Base
)

raygame_test(MathInlineAdd SOURCES arithmetic/safe_add.cpp DEPENDS Base)
raygame_test(MathInlineSub SOURCES arithmetic/safe_sub.cpp DEPENDS Base)
raygame_test(MathInlineDiv SOURCES arithmetic/safe_div.cpp DEPENDS Base)
raygame_test(MathInlineMul SOURCES arithmetic/safe_mult.cpp DEPENDS Base)

raygame_test(MathGenericInlineAdd SOURCES arithmetic/safe_add.cpp DEPENDS BaseGeneric)
target_compile_definitions(MathGenericInlineAdd PUBLIC "RAYGAME_FORCE_GENERIC_IMPL")
raygame_test(MathGenericInlineSub SOURCES arithmetic/safe_sub.cpp DEPENDS BaseGeneric)
target_compile_definitions(MathGenericInlineSub PUBLIC "RAYGAME_FORCE_GENERIC_IMPL")
raygame_test(MathGenericInlineDiv SOURCES arithmetic/safe_div.cpp DEPENDS BaseGeneric)
target_compile_definitions(MathGenericInlineDiv PUBLIC "RAYGAME_FORCE_GENERIC_IMPL")
raygame_test(MathGenericInlineMul SOURCES arithmetic/safe_mult.cpp DEPENDS BaseGeneric)
target_compile_definitions(MathGenericInlineMul PUBLIC "RAYGAME_FORCE_GENERIC_IMPL")
