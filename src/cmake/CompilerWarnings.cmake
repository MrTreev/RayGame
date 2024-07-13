function(rg_set_project_warnings project_name WARNINGS_AS_ERRORS)
    set(MSVC_WARNINGS
        /W4
        /w14242
        /w14254
        /w14263
        /w14265
        /w14287
        /we4289
        /w14296
        /w14311
        /w14545
        /w14546
        /w14547
        /w14549
        /w14555
        /w14619
        /w14640
        /w14826
        /w14905
        /w14906
        /w14928
        /permissive-
    )

    set(GCC_WARNINGS
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
    )

    set(CLANG_WARNINGS
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
    )

    set(CUDA_WARNINGS
        -Wall
        -Wextra
        -Wunused
        -Wconversion
        -Wshadow
    )

    if(WARNINGS_AS_ERRORS)
        message(TRACE "Warnings are treated as errors")
        list(APPEND CLANG_WARNINGS -Werror)
        list(APPEND GCC_WARNINGS -Werror)
        list(APPEND MSVC_WARNINGS /WX)
    endif()

    if(MSVC)
        set(PROJECT_WARNINGS_CXX ${MSVC_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
        set(PROJECT_WARNINGS_CXX ${CLANG_WARNINGS} ${CLANG_ONLY_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(PROJECT_WARNINGS_CXX ${GCC_WARNINGS})
    else()
        message(
            AUTHOR_WARNING
                "No compiler warnings set for CXX compiler: '${CMAKE_CXX_COMPILER_ID}'"
        )
    endif()

    set(PROJECT_WARNINGS_C "${PROJECT_WARNINGS_CXX}")
    set(PROJECT_WARNINGS_CUDA "${CUDA_WARNINGS}")
    target_compile_options(
        ${project_name}
        INTERFACE $<$<COMPILE_LANGUAGE:CXX>:${PROJECT_WARNINGS_CXX}>
                  $<$<COMPILE_LANGUAGE:C>:${PROJECT_WARNINGS_C}>
                  $<$<COMPILE_LANGUAGE:CUDA>:${PROJECT_WARNINGS_CUDA}>
    )
endfunction()
