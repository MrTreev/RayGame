include_guard()
include(RayGameCompilerArgs)
include(RayGameDefs)

function(raygame_bin _target)
    set(options NO_DEFS NO_ARGS)
    set(oneValueArgs)
    set(multiValueArgs SRCS DEPS DEFS)
    cmake_parse_arguments(RAYGAME_TESTARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    add_executable(${_target})
    target_compile_features(${_target} PUBLIC cxx_std_23)
    target_sources(${_target} PRIVATE ${RAYGAME_TESTARGS_SRCS})
    target_link_libraries(${_target} PRIVATE ${RAYGAME_TESTARGS_DEPS})
    target_compile_definitions(${_target} PRIVATE ${RAYGAME_TESTARGS_DEFS})
    set_target_properties(
        ${_target}
        PROPERTIES VERSION ${RayGame_VERSION}
                   CXX_VISIBILITY_PRESET hidden
                   CXX_STANDARD 23
                   CXX_STANDARD_REQUIRED YES
                   VISIBILITY_INLINES_HIDDEN YES
    )
    if($<NOT:${RAYGAME_TESTARGS_NO_DEFS}>)
        raygame_add_defs(${_target})
    endif()
    raygame_add_args(${_target})
endfunction()
