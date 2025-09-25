if(NOT RAYGAME_BUILD_DOCS)
    return()
endif()

find_package(Doxygen)

if(Doxygen_FOUND)
    set(DOXYGEN_FILE_PATTERNS *.h *.cpp *.md)
    set(DOXYGEN_HTML_COLORSTYLE "TOGGLE")
    set(DOXYGEN_QUIET YES)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${RayGame_SOURCE_DIR}/README.md")
    set(DOXYGEN_WARN_IF_UNDOCUMENTED YES)
    doxygen_add_docs(RayGameDocs ${RayGame_SOURCE_DIR}/raygame ${RayGame_SOURCE_DIR}/README.md ALL)
endif()
