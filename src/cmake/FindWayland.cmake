find_package(PkgConfig REQUIRED)
target_compile_definitions(${PROJECT_NAME} PUBLIC "RAYGAME_GUI_USE_WAYLAND")
set(RAYGAME_WL_PROTO_DIR ${CMAKE_BINARY_DIR}/protocol)
set(RAYGAME_WL_PROTO_IN ${RAYGAME_ETC}/wayland-protocols)

pkg_check_modules(WL_DEPS REQUIRED wayland-client)
if(NOT WL_DEPS_FOUND)
    message(ERROR "Could not find wayland deps")
endif()
target_compile_options(${PROJECT_NAME} PUBLIC ${WL_DEPS_CFLAGS})
target_include_directories(${PROJECT_NAME} PUBLIC ${WL_DEPS_INCLUDEDIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${WL_DEPS_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC ${RAYGAME_WL_PROTO_DIR})
execute_process(COMMAND mkdir -p ${RAYGAME_WL_PROTO_DIR})
pkg_get_variable(WaylandScanner wayland-scanner wayland_scanner)

macro(add_target_protocol target_name protoName)
    execute_process(
        COMMAND
            ${WaylandScanner} client-header
            ${RAYGAME_WL_PROTO_IN}/${protoName}.xml
            ${RAYGAME_WL_PROTO_DIR}/${protoName}-client-protocol.h
        COMMAND
            ${WaylandScanner} private-code
            ${RAYGAME_WL_PROTO_IN}/${protoName}.xml
            ${RAYGAME_WL_PROTO_DIR}/${protoName}.c
    )
    add_library(
        ${protoName}-link STATIC
        ${RAYGAME_WL_PROTO_DIR}/${protoName}-client-protocol.h
        ${RAYGAME_WL_PROTO_DIR}/${protoName}.c
    )
    set_target_properties(${protoName}-link PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(${protoName}-link PUBLIC ${WL_DEPS_INCLUDE_DIRS})
    target_link_libraries(${protoName}-link PRIVATE ${WL_DEPS_LIBRARIES})
    target_link_options(${protoName}-link PRIVATE ${WL_DEPS_LDFLAGS})
    target_link_libraries(${target_name} PUBLIC ${protoName}-link)
endmacro()
