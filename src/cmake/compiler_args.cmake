set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES CMAKE_CXX_STANDARD 23
               CMAKE_CXX_STANDARD_REQUIRED True
               CXX_EXTENSIONS OFF
               INTERPROCEDURAL_OPTIMIZATION ${ENABLE_LTO}
)

if(ENABLE_AVX)
    target_compile_options(${PROJECT_NAME} PUBLIC -mavx)
    target_compile_options(${PROJECT_NAME} PUBLIC -mavx2)
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
    target_compile_options(
        ${PROJECT_NAME} PUBLIC -fno-omit-frame-pointer -fsanitize=address
    )
endif()

if(ENABLE_MSAN)
    target_compile_options(
        ${PROJECT_NAME} PUBLIC -fno-omit-frame-pointer -fsanitize=memory
    )
endif()

if(ENABLE_UBSAN)
    target_compile_options(
        ${PROJECT_NAME} PUBLIC -fno-omit-frame-pointer -fsanitize=undefined
    )
endif()

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++23)

target_compile_options(
    ${PROJECT_NAME}
    PUBLIC -fdelete-null-pointer-checks
           -fsized-deallocation
           -fstack-protector
           -fstrict-enums
)

target_compile_options(
    ${PROJECT_NAME}
    PUBLIC -Werror
           -Wall
           -Wextra
           -Wpedantic
           -Wabi
           -Wdeprecated
           -Wdirect-ivar-access
           -Weffc++
           -Wempty-init-stmt
           -Wempty-translation-unit
           -Wexplicit-ownership-type
           -Wformat
           -Wformat-pedantic
           -Wformat-type-confusion
           -Wformat-zero-length
           -Wfour-char-constants
           -Wframe-address
           -Wgcc-compat
           -Wgnu
           -Wheader-hygiene
           -Wimplicit-function-declaration
           -Wimport-preprocessor-directive-pedantic
           -Wincompatible-function-pointer-types-strict
           -Wincomplete-module
           -Winconsistent-missing-destructor-override
           -Winfinite-recursion
           -Wint-in-bool-context
           -Wmicrosoft
           -Wmisleading-indentation
           -Wmissing-braces
           -Wmove
           -Wnewline-eof
           -Wnon-gcc
           -Wnonportable-cfstrings
           -Wnonportable-include-path
           -Wnonportable-system-include-path
           -Wnonportable-vector-initialization
           -Wnull-pointer-arithmetic
           -Wnull-pointer-subtraction
           -Wold-style-cast
           -Wpedantic-core-features
           -Wpointer-arith
           -Wrange-loop-construct
           -Wredundant-move
           -Wreserved-macro-identifier
           -Wshadow-all
           -Wsign-compare
           -Wsign-conversion
           -Wtautological-compare
           -Wthread-safety
           -Wundef
           -Wundef-prefix
           -Wunused
           -Wvariadic-macros
           -Wvector-conversion
           -Wvla
           -Wzero-as-null-pointer-constant
           -Wzero-length-array
)
