# Enable doxygen doc builds of source
function(rg_enable_doxygen )
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${PROJECT_SOURCE_DIR}/../README.md")

    # set better defaults for doxygen
	set(DOXYGEN_QUIET YES)
    set(DOXYGEN_CALLER_GRAPH YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_DOT_IMAGE_FORMAT svg)
    set(DOXYGEN_DOT_TRANSPARENT YES)

    # find doxygen and dot if available
    find_package(Doxygen REQUIRED OPTIONAL_COMPONENTS dot)

    # add doxygen-docs target
    message(STATUS "Adding `doxygen-docs` target that builds the documentation.")
    doxygen_add_docs(
        doxygen-docs ALL ${PROJECT_SOURCE_DIR}
        COMMENT "Generating documentation - entry file: ${CMAKE_CURRENT_BINARY_DIR}/html/index.html"
                CONFIG_FILE "${RG_PATH_ETC}/doxygen/Doxyfile"
    )
endfunction()
