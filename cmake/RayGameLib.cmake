include(RayGameCompilerArgs)
include(RayGameDefs)
function(raygame_lib _full_target)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs HEADERS SRCS DEPS DEFS)
    cmake_parse_arguments(RAYGAME_TESTARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    string(REPLACE ":" "" _target ${_full_target})
    add_library(${_target})
    add_library(${_full_target} ALIAS ${_target})
    target_compile_features(${_target} PUBLIC cxx_std_23)
    target_include_directories(
        ${_target} PUBLIC $<BUILD_INTERFACE:${RayGame_SOURCE_DIR}> $<INSTALL_INTERFACE:include/raygame>
    )
    target_sources(${_target}
        PUBLIC ${RAYGAME_TESTARGS_HEADERS}
        PRIVATE ${RAYGAME_TESTARGS_SRCS}
    )
    target_link_libraries(${_target} PRIVATE ${RAYGAME_TESTARGS_DEPS})
    target_compile_definitions(${_target} PUBLIC ${RAYGAME_TESTARGS_DEFS})
    set_target_properties(
        ${_target}
        PROPERTIES VERSION ${RayGame_VERSION}
                   CXX_VISIBILITY_PRESET hidden
                   CXX_STANDARD 23
                   CXX_STANDARD_REQUIRED YES
                   VISIBILITY_INLINES_HIDDEN YES
    )
    raygame_add_args(${_target})
    raygame_add_defs(${_target})
endfunction()
