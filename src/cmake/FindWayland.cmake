if(RAYGAME_GUI_USE_WAYLAND)
    find_package(PkgConfig REQUIRED)
    target_compile_definitions(
        ${PROJECT_NAME} PRIVATE "RAYGAME_GUI_USE_WAYLAND"
    )
    set(RAYGAME_WL_PROTO_DIR ${CMAKE_BINARY_DIR}/protocol)
    set(RAYGAME_WL_PROTO_IN ${RAYGAME_ETC}/wayland-protocols)
    pkg_check_modules(
        wayland-deps
        REQUIRED
        IMPORTED_TARGET
        wayland-client
    )
    pkg_get_variable(WaylandScanner wayland-scanner wayland_scanner)
    function(protocol protoName)
        execute_process(COMMAND mkdir -p ${RAYGAME_WL_PROTO_DIR})
        execute_process(
            COMMAND
                ${WaylandScanner} server-header
                ${RAYGAME_WL_PROTO_IN}/${protoName}.xml
                ${RAYGAME_WL_PROTO_DIR}/${protoName}.h
        )
        execute_process(
            COMMAND
                ${WaylandScanner} private-code
                ${RAYGAME_WL_PROTO_IN}/${protoName}.xml
                ${RAYGAME_WL_PROTO_DIR}/${protoName}.c
        )
        target_sources(
            ${PROJECT_NAME} PRIVATE ${RAYGAME_WL_PROTO_DIR}/${protoName}.c
        )
    endfunction()

    protocol(xdg-shell)

    target_link_libraries(${PROJECT_NAME} wayland-client)
    target_include_directories(
        ${PROJECT_NAME} SYSTEM PUBLIC ${RAYGAME_WL_PROTO_DIR}
    )
endif()
