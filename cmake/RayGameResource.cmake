include_guard()


function(raygame_lib _target)
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs RESOURCES)
    cmake_parse_arguments(RAYGAME_TESTARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    set(${RAYGAME_TESTARGS_NAME}_header "${RAYGAME_TESTARGS_NAME}.h")
    set(${RAYGAME_TESTARGS_NAME}_source "${RAYGAME_TESTARGS_NAME}.cpp")
    set_source_files_properties(${${RAYGAME_TESTARGS_NAME}_source} GENERATED)
    set_source_files_properties(${${RAYGAME_TESTARGS_NAME}_header} GENERATED)
    set_property(SOURCE ${${RAYGAME_TESTARGS_NAME}_header} ${${RAYGAME_TESTARGS_NAME}_source} PROPERTY SKIP_AUTOMOC ON)
    add_custom_command(
        OUTPUT ${${RAYGAME_TESTARGS_NAME}_header} ${${RAYGAME_TESTARGS_NAME}_source}
        COMMAND ${RAYGAME_RESMK_EXE} ${${RAYGAME_TESTARGS_NAME}_header} ${RAYGAME_TESTARGS_RESOURCES}
        DEPENDS RayGame::Tools::ResMk
        VERBATIM
    )

    add_library(${_target})
    target_include_directories(${_target} PUBLIC $<BUILD_INTERFACE:${RayGame_SOURCE_DIR}> $<INSTALL_INTERFACE:include/raygame>)
endfunction()
