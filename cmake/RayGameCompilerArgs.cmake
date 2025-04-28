function(raygame_add_args _target)
    if(MSVC)
        target_compile_options(${_target} PRIVATE /W4)          # Baseline reasonable warnings
        target_compile_options(${_target} PRIVATE /w14242)      # 'identifier': conversion from 'type1' to 'type2', possible loss of data
        target_compile_options(${_target} PRIVATE /w14254)      # 'operator': conversion from 'type1:field_bits' to 'type2:field_bits', possible loss of data
        target_compile_options(${_target} PRIVATE /w14263)      # 'function': member function does not override any base class virtual member function
        target_compile_options(${_target} PRIVATE /w14265)      # 'classname': class has virtual functions, but destructor is not virtual instances of this class may not be destructed correctly
        target_compile_options(${_target} PRIVATE /w14287)      # 'operator': unsigned/negative constant mismatch
        target_compile_options(${_target} PRIVATE /we4289)      # nonstandard extension used: 'variable': loop control variable declared in the for-loop is used outside the for-loop scope
        target_compile_options(${_target} PRIVATE /w14296)      # 'operator': expression is always 'boolean_value'
        target_compile_options(${_target} PRIVATE /w14311)      # 'variable': pointer truncation from 'type1' to 'type2'
        target_compile_options(${_target} PRIVATE /w14545)      # expression before comma evaluates to a function which is missing an argument list
        target_compile_options(${_target} PRIVATE /w14546)      # function call before comma missing argument list
        target_compile_options(${_target} PRIVATE /w14547)      # 'operator': operator before comma has no effect; expected operator with side-effect
        target_compile_options(${_target} PRIVATE /w14549)      # 'operator': operator before comma has no effect; did you intend 'operator'?
        target_compile_options(${_target} PRIVATE /w14555)      # expression has no effect; expected expression with side- effect
        target_compile_options(${_target} PRIVATE /w14619)      # pragma warning: there is no warning number 'number'
        target_compile_options(${_target} PRIVATE /w14640)      # Enable warning on thread un-safe static member initialization
        target_compile_options(${_target} PRIVATE /w14826)      # Conversion from 'type1' to 'type2' is sign-extended. This may cause unexpected runtime behavior.
        target_compile_options(${_target} PRIVATE /w14905)      # wide string literal cast to 'LPSTR'
        target_compile_options(${_target} PRIVATE /w14906)      # string literal cast to 'LPWSTR'
        target_compile_options(${_target} PRIVATE /w14928)      # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
        target_compile_options(${_target} PRIVATE /permissive-) # standards conformance mode for MSVC compiler.
        target_compile_options(${_target} PRIVATE ${RAYGAME_MSVC_OPTIONS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
        target_compile_options(${_target} PRIVATE -Wall)
        target_compile_options(${_target} PRIVATE -Wextra)
        target_compile_options(${_target} PRIVATE -Weverything)
        target_compile_options(${_target} PRIVATE -pedantic)
        target_compile_options(${_target} PRIVATE -Wthread-safety)
        target_compile_options(${_target} PRIVATE -Wself-assign)
        target_compile_options(${_target} PRIVATE -Wno-padded)
        target_compile_options(${_target} PRIVATE -Wno-c99-extensions)
        target_compile_options(${_target} PRIVATE -Wno-c99-compat)
        target_compile_options(${_target} PRIVATE -Wno-c++-compat)
        target_compile_options(${_target} PRIVATE -Wno-c++98-compat)
        target_compile_options(${_target} PRIVATE -Wno-c++98-compat-pedantic)
        target_compile_options(${_target} PRIVATE -Wno-c++20-compat)
        target_compile_options(${_target} PRIVATE -Wno-pre-c++20-compat-pedantic)
        target_compile_options(${_target} PRIVATE -Wno-pre-c++17-compat-pedantic)
        target_compile_options(${_target} PRIVATE -Wno-switch-default)
        target_compile_options(${_target} PRIVATE -Wno-c++20-extensions)
        target_compile_options(${_target} PRIVATE -Wno-unused-macros)
        target_compile_options(${_target} PRIVATE -Wno-unsafe-buffer-usage)
        target_compile_options(${_target} PRIVATE -Wno-c23-extensions)
        target_compile_options(${_target} PRIVATE ${RAYGAME_CLANG_OPTIONS})
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${_target} PRIVATE -Wall)
        target_compile_options(${_target} PRIVATE -Wextra)
        target_compile_options(${_target} PRIVATE -Wshadow)                 # warn the user if a variable declaration shadows one from a parent context
        target_compile_options(${_target} PRIVATE -Wnon-virtual-dtor)       # warn the user if a class with virtual functions has a non-virtual destructor.
        target_compile_options(${_target} PRIVATE -Wold-style-cast)         # warn for c-style casts
        target_compile_options(${_target} PRIVATE -Wcast-align)             # warn for potential performance problem casts
        target_compile_options(${_target} PRIVATE -Wunused)                 # warn on anything being unused
        target_compile_options(${_target} PRIVATE -Woverloaded-virtual)     # warn if you overload (not override) a virtual function
        target_compile_options(${_target} PRIVATE -Wpedantic)               # warn if non-standard C++ is used
        target_compile_options(${_target} PRIVATE -Wconversion)             # warn on type conversions that may lose data
        target_compile_options(${_target} PRIVATE -Wsign-conversion)        # warn on sign conversions
        target_compile_options(${_target} PRIVATE -Wnull-dereference)       # warn if a null dereference is detected
        target_compile_options(${_target} PRIVATE -Wdouble-promotion)       # warn if float is implicit promoted to double
        target_compile_options(${_target} PRIVATE -Wformat=2)               # warn on security issues around functions that format output (ie printf)
        target_compile_options(${_target} PRIVATE -Wimplicit-fallthrough)   # warn on statements that fallthrough without an explicit annotation
        target_compile_options(${_target} PRIVATE -Wmisleading-indentation) # warn if indentation implies blocks where blocks do not exist
        target_compile_options(${_target} PRIVATE -Wduplicated-cond)        # warn if if / else chain has duplicated conditions
        target_compile_options(${_target} PRIVATE -Wduplicated-branches)    # warn if if / else branches have duplicated code
        target_compile_options(${_target} PRIVATE -Wlogical-op)             # warn about logical operations being used where bitwise were probably wanted
        target_compile_options(${_target} PRIVATE -Wuseless-cast)           # warn if you perform a cast to the same type
        target_compile_options(${_target} PRIVATE -Wsuggest-override)       # warn if an overridden member function is not marked 'override' or 'final'
        target_compile_options(${_target} PRIVATE -Wno-return-type)         # Too many false-positives
        target_compile_options(${_target} PRIVATE -Wno-duplicate-branches)  # Too many false-positives
        target_compile_options(${_target} PRIVATE ${RAYGAME_GCC_OPTIONS})
    else()
        message(AUTHOR_WARNING "No compiler warnings set for CXX compiler: '${CMAKE_CXX_COMPILER_ID}'")
    endif()
endfunction()
