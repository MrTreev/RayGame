# SFML
include(ExternalProject)
include(FindX11)
ExternalProject_Add(
    DFPSR
    GIT_REPOSITORY https://github.com/Dawoodoz/DFPSR.git
    GIT_SUBMODULES_RECURSE ON
    PREFIX _deps
    DOWNLOAD_DIR _deps
    SOURCE_DIR _deps/DFPSR
    BINARY_DIR _deps/DFPSR-build
    STAMP_DIR _deps/DFPSR-stamp
    UPDATE_DISCONNECTED ON
    CONFIGURE_COMMAND "${CMAKE_CURRENT_BINARY_DIR}/_deps/DFPSR/Source/tools/builder/buildProject.sh"
    BUILD_COMMAND
        "${CMAKE_CURRENT_BINARY_DIR}/_deps/DFPSR/Source/tools/buildLibrary.sh"
        "${CMAKE_CXX_COMPILER}"
        "${CMAKE_CURRENT_BINARY_DIR}/_deps/DFPSR/Source/DFPSR"
        "${CMAKE_CURRENT_BINARY_DIR}/_deps/DFPSR-build" "DFPSR"
		"${CMAKE_CXX_FLAGS} -lX11" "CLEAN"
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/_deps/DFPSR-build/DFPSR.a"
    BUILD_BYPRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/_deps/DFPSR/Source"
)
target_include_directories(
    ${PROJECT_NAME} SYSTEM BEFORE
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/_deps/DFPSR/Source ${X11_INCLUDE_DIR}
)
target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/_deps/DFPSR-build/DFPSR.a"
           "${X11_LIBRARIES}"
)
