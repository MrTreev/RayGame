option(BUILD_DOC "Build documentation" OFF)
if (BUILD_DOC)
	find_package(Doxygen)
	if (DOXYGEN_FOUND)
	    # set input and output files
	    set(DOXYFILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
	    message("Doxygen build started")
	    add_custom_target( doc_doxygen ALL
	        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
	        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	        COMMENT "Generating API documentation with Doxygen"
	        VERBATIM )
	else (DOXYGEN_FOUND)
	  message("Doxygen need to be installed to generate the doxygen documentation")
	endif (DOXYGEN_FOUND)
endif (BUILD_DOC)
