raygame_core_lib(
    Window
    SOURCES
    window.cpp
    HEADERS
    window.h
    PUBLIC_DEPENDS
    Base
    Math
    Drawing
)

if(RAYGAME_ENABLE_WAYLAND)
	function(raygame_target_client_protocol)
	    set(options)
	    set(oneValueArgs TARGET)
	    set(multiValueArgs PROTOCOLS)
	    cmake_parse_arguments(RAYGAME_ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
	    find_package(PkgConfig)
	    pkg_check_modules(RAYGAME_WL REQUIRED wayland-client)
	    if(NOT RAYGAME_WL_FOUND)
	        message(SEND_ERROR "wayland-client module could not be found")
	    endif()
	
	    find_program(WAYLAND_SCANNER_EXECUTABLE NAMES wayland-scanner)
	    set(${RAYGAME_ARGS_TARGET}_proto_dir "${CMAKE_CURRENT_BINARY_DIR}/wayland")
	
	    add_library(${RAYGAME_ARGS_TARGET}_wayland SHARED)
	    set_target_properties(
	        ${RAYGAME_ARGS_TARGET}_wayland
	        PROPERTIES COMPILER_WARNING_AS_ERROR OFF
	                   LANGUAGE C
	                   C_EXTENSIONS OFF
	                   C_STANDARD 23
	                   LINKER_LANGUAGE C
	                   SYSTEM ON
	    )
	
	    foreach(protocol IN LISTS RAYGAME_ARGS_PROTOCOLS)
	        set(${protocol}_header "${${RAYGAME_ARGS_TARGET}_proto_dir}/${protocol}-client-protocol.h")
	        set(${protocol}_source "${${RAYGAME_ARGS_TARGET}_proto_dir}/${protocol}-protocol.c")
	        set(${protocol}_xml "${RAYGAME_PATH_ETC}/wayland-protocols/${protocol}.xml")
	        set_source_files_properties(${${protocol}_source} GENERATED)
	        set_source_files_properties(${${protocol}_header} GENERATED)
	        set_property(SOURCE ${${protocol}_header} ${${protocol}_source} PROPERTY SKIP_AUTOMOC ON)
	        add_custom_command(
	            OUTPUT "${${protocol}_source}"
	            COMMAND ${WAYLAND_SCANNER_EXECUTABLE} public-code ${${protocol}_xml} ${${protocol}_source}
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
	            ${RAYGAME_ARGS_TARGET}_wayland
	            PUBLIC ${${protocol}_header}
	            PRIVATE ${${protocol}_source}
	        )
	    endforeach()
	
	    target_include_directories(
	        ${RAYGAME_ARGS_TARGET}_wayland
	        PUBLIC ${${RAYGAME_ARGS_TARGET}_proto_dir}
	        PRIVATE ${RAYGAME_WL_INCLUDE_DIRS}
	    )
	    target_link_libraries(${RAYGAME_ARGS_TARGET}_wayland PUBLIC ${RAYGAME_WL_LINK_LIBRARIES})
	    target_link_options(${RAYGAME_ARGS_TARGET}_wayland PRIVATE ${RAYGAME_WL_LDFLAGS})
	    target_compile_options(${RAYGAME_ARGS_TARGET}_wayland PRIVATE ${RAYGAME_WL_CFLAGS})
	    target_include_directories(${RAYGAME_ARGS_TARGET} PUBLIC ${${RAYGAME_ARGS_TARGET}_proto_dir})
	    target_link_libraries(${RAYGAME_ARGS_TARGET} PUBLIC ${RAYGAME_ARGS_TARGET}_wayland)
	endfunction()
    target_sources(Window PRIVATE wayland.h wayland.cpp detail/wayland.h detail/wayland.cpp)
    raygame_target_client_protocol(TARGET Window PROTOCOLS wayland xdg-shell)
    target_link_libraries(Window PUBLIC xkbcommon)
endif()
if(RAYGAME_ENABLE_X11)
    target_sources(Window PRIVATE x11.cpp x11.h)
    target_link_libraries(Window PRIVATE X11)
endif()
