#!/bin/sh

GCC_WARNINGS<<-END_GCC_WARNINGS
-Wall
-Wextra
-Wshadow
-Wdeprecated
-Wabi
-Wcast-align
-Wconversion
-Wdouble-promotion
-Wduplicated-branches
-Wduplicated-cond
-Weffc++
-Wformat-zero-length
-Wformat=2
-Wframe-address
-Wimplicit
-Wimplicit-fallthrough
-Wimplicit-function-declaration
-Wimplicit-int
-Wimplicit-interface
-Wimplicit-procedure
-Winfinite-recursion
-Wint-in-bool-context
-Wlogical-op
-Wmisleading-indentation
-Wmissing-braces
-Wnon-virtual-dtor
-Wnull-dereference
-Wold-style-cast
-Woverloaded-virtual
-Wpedantic
-Wpointer-arith
-Wrange-loop-construct
-Wredundant-move
-Wsign-compare
-Wsign-conversion
-Wsuggest-override
-Wtautological-compare
-Wundef
-Wunused
-Wuseless-cast
-Wvariadic-macros
-Wvla
-Wzero-as-null-pointer-constant
-Wzero-length-array
END_GCC_WARNINGS

CLANG_WARNINGS<<-END_CLANG_WARNINGS
${GCC_WARNINGS}
-Weverything
-Wdirect-ivar-access
-Wempty-init-stmt
-Wempty-translation-unit
-Wexplicit-ownership-type
-Wformat-pedantic
-Wformat-type-confusion
-Wfour-char-constants
-Wgcc-compat
-Wgnu
-Wheader-hygiene
-Wimport-preprocessor-directive-pedantic
-Wincompatible-function-pointer-types-strict
-Wincomplete-module
-Winconsistent-missing-destructor-override
-Wlifetime
-Wmicrosoft
-Wmove
-Wnewline-eof
-Wnon-gcc
-Wnonportable-cfstrings
-Wnonportable-include-path
-Wnonportable-system-include-path
-Wnonportable-vector-initialization
-Wnull-pointer-arithmetic
-Wnull-pointer-subtraction
-Wpedantic-core-features
-Wreserved-macro-identifier
-Wshadow-all
-Wthread-safety
-Wundef-prefix
-Wvector-conversion
END_CLANG_WARNINGS

DEBUG_ARGS<<-END_DEBUG_ARGS
-Og
-ggdb
-fno-omit-frame-pointer
END_DEBUG_ARGS

OPT_ARGS<<-END_OPT_ARGS
-Ofast
END_OPT_ARGS

GCC_ARGS<<-END_GCC_ARGS
-fdiagnostics-color=always
END_GCC_ARGS

CLANG_ARGS<<-END_CLANG_ARGS
-fcolor-diagnostics
END_CLANG_ARGS

SANITIZE_ADDRESS_ARGS<<-END_SANITIZE_ADDRESS_ARGS
-fno-omit-frame-pointer
-fsanitize=address
-fsanitize-address-use-after-return=always
-fsanitize-address-use-after-scope
END_SANITIZE_ADDRESS_ARGS

SANITIZE_MEMORY_ARGS<<-END_SANITIZE_MEMORY_ARGS
-fno-omit-frame-pointer
-fsanitize=memory
END_SANITIZE_MEMORY_ARGS

SANITIZE_UNDEFINED_BEHAVIOUR_ARGS<<-END_SANITIZE_UNDEFINED_BEHAVIOUR_ARGS
-fno-omit-frame-pointer
-fsanitize=undefined
-fsanitize=local-bounds
-fsanitize=float-divide-by-zero
-fsanitize=implicit-conversion
-fsanitize=nullability
END_SANITIZE_UNDEFINED_BEHAVIOUR_ARGS

if [ "${COMPILER}" = "clang++" ]; then
    CPPFLAGS="$(echo "${CLANG_FLAGS}" | tr '\n' ' ')"
else
    CPPFLAGS="$(echo "${GCC_FLAGS}" | tr '\n' ' ')"
fi

if [ "${BUILD_TYPE}" = "DEBUG" ]; then
    CPPFLAGS="${CPPFLAGS} $(echo "${DEBUG_ARGS}" | tr '\n' ' ')"
else
    CPPFLAGS="${CPPFLAGS} $(echo "${OPT_ARGS}" | tr '\n' ' ')"
fi

if [ "${SANITIZE_ADDRESS}" = "YES" ]; then
    CPPFLAGS="${CPPFLAGS} $(echo "${SANITIZE_ADDRESS_ARGS}" | tr '\n' ' ')"
fi
if [ "${SANITIZE_MEMORY}" = "YES" ]; then
    CPPFLAGS="${CPPFLAGS} $(echo "${SANITIZE_MEMORY_ARGS}" | tr '\n' ' ')"
fi

if [ "${SANITIZE_UNDEFINED_BEHAVIOUR}" = "YES" ]; then
    CPPFLAGS="${CPPFLAGS} $(echo "${SANITIZE_UNDEFINED_BEHAVIOUR_ARGS}" | tr '\n' ' ')"
fi
