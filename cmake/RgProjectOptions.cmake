set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

option(RG_BUILD_DOC "Build documentation" ON)
option(RG_TEST_ENABLE "Build and run tests" ON)
option(RG_RUN_TESTS "Run tests in build" ON)
option(RG_RUN_GAME "Run game in build" OFF)

option(RG_WARNINGS_AS_ERRORS "Warnings as errors" ON)

option(RG_ENABLE_WAYLAND "Enable Wayland Backend" ON)
option(RG_IGNORE_CONDITIONS "Ignore all runtime condition checks" OFF)

option(RG_ENABLE_AVX "Enable AVX instructions" ON)
option(RG_ENABLE_LTO "Enable Link-Time Optimisation" OFF)

option(RG_ENABLE_ASAN "Enable the Address Sanitiser" OFF)
option(RG_ENABLE_MSAN "Enable the Memory Sanitiser" OFF)
option(RG_ENABLE_UBSAN "Enable the Undefined Behaviour Sanitiser" OFF)

option(RG_ENABLE_COMPILE_COMMANDS "Create compile_commands.json file" ON)
option(RG_ENABLE_CLANG_TIDY "Enable Clang Tidy" ON)
option(RG_ENABLE_SOURCE_LOCATION "Enable source_location in logs" ON)

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
set_property(
    CACHE RG_LOG_LEVEL
    PROPERTY STRINGS
             "TRACE"
             "DEBUG"
             "INFO"
             "NOTE"
             "PROGRESS"
             "WARNING"
             "ERROR"
             "FATAL"
)

if(RG_ENABLE_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

if(RG_WARNINGS_AS_ERRORS)
    add_compile_options(-Werror)
endif()

if(RG_LIBCPP)
    add_compile_options(-stdlib=libc++ -lc++abi)
    add_link_options(-stdlib=libc++ -lc++abi)
endif()
