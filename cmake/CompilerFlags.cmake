option(ENABLE_ASAN "Enable the Address Sanitiser" OFF)
option(ENABLE_MSAN "Enable the Memory Sanitiser" OFF)
option(ENABLE_UBSAN "Enable the Undefined Behaviour Sanitiser" OFF)
option(ENABLE_LTO "Enable Link-Time Optimisation" OFF)
option(RAYGAME_IGNORE_CONDITIONS "Ignore all runtime condition checks" OFF)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_LOG_DEBUG")
    target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_LOG_LOCATION")
    target_compile_options(${PROJECT_NAME} PUBLIC -Og)
    target_compile_options(${PROJECT_NAME} PUBLIC -ggdb)
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_LOG_INFO")
    target_compile_options(${PROJECT_NAME} PUBLIC -Ofast)
endif()

if(RAYGAME_IGNORE_CONDITIONS)
    target_compile_definitions(
        ${PROJECT_NAME} PUBLIC "RAYGAME_IGNORE_CONDITIONS"
    )
endif()

if(ENABLE_LTO)
    set_target_properties(
        ${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE
    )
endif()

if(ENABLE_MSAN AND ENABLE_ASAN)
    message(
        WARNING
            "Compiling with both AddressSanitizer and MemorySanitizer is not recommended"
    )
endif()

if(ENABLE_ASAN)
    target_compile_options(${PROJECT_NAME} PUBLIC -fno-omit-frame-pointer)
    target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
endif()

if(ENABLE_MSAN)
    target_compile_options(${PROJECT_NAME} PUBLIC -fno-omit-frame-pointer)
    target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=memory)
endif()

if(ENABLE_UBSAN)
    target_compile_options(${PROJECT_NAME} PUBLIC -fno-omit-frame-pointer)
    target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=undefined)
endif()

target_compile_options(${PROJECT_NAME} PUBLIC -std=c++23)
target_compile_options(${PROJECT_NAME} PUBLIC -fdelete-null-pointer-checks)
target_compile_options(${PROJECT_NAME} PUBLIC -fsized-deallocation)
target_compile_options(${PROJECT_NAME} PUBLIC -fstack-protector)
target_compile_options(${PROJECT_NAME} PUBLIC -fstrict-enums)

target_compile_options(${PROJECT_NAME} PUBLIC -Wall)
target_compile_options(${PROJECT_NAME} PUBLIC -Wextra)
target_compile_options(${PROJECT_NAME} PUBLIC -Wpedantic)
target_compile_options(${PROJECT_NAME} PUBLIC -Wdeprecated)
target_compile_options(${PROJECT_NAME} PUBLIC -Wabi)
target_compile_options(${PROJECT_NAME} PUBLIC -Wdirect-ivar-access)
target_compile_options(${PROJECT_NAME} PUBLIC -Weffc++)
target_compile_options(${PROJECT_NAME} PUBLIC -Wempty-init-stmt)
target_compile_options(${PROJECT_NAME} PUBLIC -Wempty-translation-unit)
target_compile_options(${PROJECT_NAME} PUBLIC -Wexplicit-ownership-type)
target_compile_options(${PROJECT_NAME} PUBLIC -Wformat)
target_compile_options(${PROJECT_NAME} PUBLIC -Wformat-pedantic)
target_compile_options(${PROJECT_NAME} PUBLIC -Wformat-type-confusion)
target_compile_options(${PROJECT_NAME} PUBLIC -Wformat-zero-length)
target_compile_options(${PROJECT_NAME} PUBLIC -Wfour-char-constants)
target_compile_options(${PROJECT_NAME} PUBLIC -Wframe-address)
target_compile_options(${PROJECT_NAME} PUBLIC -Wgcc-compat)
target_compile_options(${PROJECT_NAME} PUBLIC -Wgnu)
target_compile_options(${PROJECT_NAME} PUBLIC -Wheader-hygiene)
target_compile_options(
    ${PROJECT_NAME} PUBLIC -Wimport-preprocessor-directive-pedantic
)
target_compile_options(${PROJECT_NAME} PUBLIC -Wimplicit-function-declaration)
target_compile_options(
    ${PROJECT_NAME} PUBLIC -Wincompatible-function-pointer-types-strict
)
target_compile_options(${PROJECT_NAME} PUBLIC -Wincomplete-module)
target_compile_options(
    ${PROJECT_NAME} PUBLIC -Winconsistent-missing-destructor-override
)
target_compile_options(${PROJECT_NAME} PUBLIC -Winfinite-recursion)
target_compile_options(${PROJECT_NAME} PUBLIC -Wint-in-bool-context)
target_compile_options(${PROJECT_NAME} PUBLIC -Wmicrosoft)
target_compile_options(${PROJECT_NAME} PUBLIC -Wmisleading-indentation)
target_compile_options(${PROJECT_NAME} PUBLIC -Wmissing-braces)
target_compile_options(${PROJECT_NAME} PUBLIC -Wmove)
target_compile_options(${PROJECT_NAME} PUBLIC -Wnewline-eof)
target_compile_options(${PROJECT_NAME} PUBLIC -Wnon-gcc)
target_compile_options(${PROJECT_NAME} PUBLIC -Wnonportable-cfstrings)
target_compile_options(${PROJECT_NAME} PUBLIC -Wnonportable-include-path)
target_compile_options(${PROJECT_NAME} PUBLIC -Wnonportable-system-include-path)
target_compile_options(
    ${PROJECT_NAME} PUBLIC -Wnonportable-vector-initialization
)
target_compile_options(${PROJECT_NAME} PUBLIC -Wnull-pointer-arithmetic)
target_compile_options(${PROJECT_NAME} PUBLIC -Wnull-pointer-subtraction)
target_compile_options(${PROJECT_NAME} PUBLIC -Wold-style-cast)
target_compile_options(${PROJECT_NAME} PUBLIC -Wpedantic-core-features)
target_compile_options(${PROJECT_NAME} PUBLIC -Wpointer-arith)
target_compile_options(${PROJECT_NAME} PUBLIC -Wrange-loop-construct)
target_compile_options(${PROJECT_NAME} PUBLIC -Wredundant-move)
target_compile_options(${PROJECT_NAME} PUBLIC -Wreserved-macro-identifier)
target_compile_options(${PROJECT_NAME} PUBLIC -Wshadow-all)
target_compile_options(${PROJECT_NAME} PUBLIC -Wsign-compare)
target_compile_options(${PROJECT_NAME} PUBLIC -Wsign-conversion)
target_compile_options(${PROJECT_NAME} PUBLIC -Wtautological-compare)
target_compile_options(${PROJECT_NAME} PUBLIC -Wthread-safety)
target_compile_options(${PROJECT_NAME} PUBLIC -Wundef)
target_compile_options(${PROJECT_NAME} PUBLIC -Wundef-prefix)
target_compile_options(${PROJECT_NAME} PUBLIC -Wunused)
target_compile_options(${PROJECT_NAME} PUBLIC -Wvariadic-macros)
target_compile_options(${PROJECT_NAME} PUBLIC -Wvector-conversion)
target_compile_options(${PROJECT_NAME} PUBLIC -Wvla)
target_compile_options(${PROJECT_NAME} PUBLIC -Wzero-as-null-pointer-constant)
target_compile_options(${PROJECT_NAME} PUBLIC -Wzero-length-array)
