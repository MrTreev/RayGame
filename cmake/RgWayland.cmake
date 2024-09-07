function(rg_target_client_protocol)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs PROTOCOLS)
    cmake_parse_arguments(RG_ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    find_package(PkgConfig)

    find_program(WAYLAND_SCANNER_EXECUTABLE NAMES wayland-scanner)
    set(${RG_ARGS_TARGET}_proto_dir "${CMAKE_CURRENT_BINARY_DIR}/wayland")

    add_library(${RG_ARGS_TARGET}_wayland SHARED)
    set_target_properties(
        ${RG_ARGS_TARGET}_wayland
        PROPERTIES COMPILER_WARNING_AS_ERROR OFF
                   C_EXTENSIONS OFF
                   LINKER_LANGUAGE C
                   SYSTEM ON
    )

    foreach(protocol IN LISTS RG_ARGS_PROTOCOLS)
        set(${protocol}_header "${${RG_ARGS_TARGET}_proto_dir}/${protocol}-client-protocol.h")
        set(${protocol}_source "${${RG_ARGS_TARGET}_proto_dir}/wayland/${protocol}-protocol.cpp")
        set(${protocol}_xml "${RG_PATH_ETC}/wayland-protocols/${protocol}.xml")

        set_source_files_properties(${${protocol}_source} GENERATED)
        set_source_files_properties(${${protocol}_header} GENERATED)
        set_property(SOURCE ${${protocol}_header} ${${protocol}_source} PROPERTY SKIP_AUTOMOC ON)

        add_custom_command(
            OUTPUT "${${protocol}_source}"
            COMMAND ${WAYLAND_SCANNER_EXECUTABLE} private-code ${${protocol}_xml} ${${protocol}_source}
            DEPENDS ${${protocol}_xml}
            VERBATIM
        )
        add_custom_command(
            OUTPUT "${${protocol}_header}"
            COMMAND ${WAYLAND_SCANNER_EXECUTABLE} client-header ${${protocol}_xml} ${${protocol}_header}
            DEPENDS ${${protocol}_xml}
            VERBATIM
        )
        target_sources(
            ${RG_ARGS_TARGET}_wayland
            PUBLIC ${${protocol}_header}
            PRIVATE ${${protocol}_source}
        )
    endforeach()

    pkg_check_modules(RG_WL REQUIRED wayland-client)
    if(NOT RG_WL_FOUND)
        message(SEND_ERROR "wayland-client module could not be found")
    endif()
    target_include_directories(${RG_ARGS_TARGET}_wayland PRIVATE ${RG_WL_INCLUDE_DIRS})
    target_link_libraries(${RG_ARGS_TARGET}_wayland PRIVATE ${RG_WL_LINK_LIBRARIES})
    target_link_options(${RG_ARGS_TARGET}_wayland PRIVATE ${RG_WL_LDFLAGS})
    target_compile_options(${RG_ARGS_TARGET}_wayland PRIVATE ${RG_WL_CFLAGS})
endfunction()
