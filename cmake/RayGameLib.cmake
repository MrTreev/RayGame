include_guard()
include(RayGameSetup)
include(RayGameCompilerArgs)
include(RayGameDefs)

function(raygame_lib _target)
    set(options NO_INCS)
    set(oneValueArgs)
    set(multiValueArgs HDRS SRCS DEPS DEFS)
    cmake_parse_arguments(RAYGAME_TESTARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    add_library(${_target})
    target_compile_features(${_target} PUBLIC cxx_std_23)
    if(NOT RAYGAME_TESTARGS_NO_INCS)
        target_include_directories(
            ${_target} PUBLIC $<BUILD_INTERFACE:${RayGame_SOURCE_DIR}> $<INSTALL_INTERFACE:include/raygame>
        )
    endif()
    target_sources(${_target}
        PUBLIC ${RAYGAME_TESTARGS_HDRS}
        PRIVATE ${RAYGAME_TESTARGS_SRCS}
    )
    target_link_libraries(${_target} PRIVATE ${RAYGAME_TESTARGS_DEPS})
    target_compile_definitions(${_target} PUBLIC ${RAYGAME_TESTARGS_DEFS})
    set_target_properties(
        ${_target}
        PROPERTIES VERSION ${RayGame_VERSION}
                   LINKER_LANGUAGE CXX
                   CXX_VISIBILITY_PRESET hidden
                   CXX_STANDARD 23
                   CXX_STANDARD_REQUIRED YES
                   VISIBILITY_INLINES_HIDDEN YES
    )
    raygame_add_args(${_target})
    raygame_add_defs(${_target})
endfunction()
