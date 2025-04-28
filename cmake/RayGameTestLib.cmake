set(RAYGAME_TESTLIB "DOCTEST" CACHE STRING "Testing library used for RayGame")
set_property(CACHE RAYGAME_TESTLIB PROPERTY STRINGS "DOCTEST" "GTEST")

set(RAYGAME_TESTLIB_USE_SYSTEM ON CACHE BOOL "Use system version of testing library")

macro(raygame_enable_testing)
    if(RAYGAME_TESTLIB STREQUAL "DOCTEST")
        if(RAYGAME_TESTLIB_USE_SYSTEM)
            find_package(doctest)
        else()
            include(ExternalProject)
            find_package(Git REQUIRED)
            ExternalProject_Add(doctest
                PREFIX ${CMAKE_BINARY_DIR}/doctest
                SOURCE_DIR ${CMAKE_SOURCE_DIR}/third_party/doctest
                GIT_REPOSITORY https://github.com/doctest/doctest.git
                GIT_TAG master
                UPDATE_COMMAND ${GIT_EXECUTABLE} pull
                CONFIGURE_COMMAND ""
                BUILD_COMMAND ""
                INSTALL_COMMAND ""
            )
            ExternalProject_Get_Property(doctest source_dir)
            set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")
        endif()
    elseif(RAYGAME_TESTLIB STREQUAL "GTEST")
        find_package(GTest REQUIRED)
    else()
        message(CHECK_FAIL "Invalid test library given")
    endif()
    enable_testing()
    include(CTest)
endmacro()

function(raygame_link_testlib _target)
    if(RAYGAME_TESTLIB STREQUAL "DOCTEST")
        target_compile_definitions(${_target} PRIVATE RAYGAME_TESTLIB_DOCTEST)
        target_link_libraries(${_target} PUBLIC doctest::doctest)
    elseif(RAYGAME_TESTLIB STREQUAL "GTEST")
        target_compile_definitions(${_target} PRIVATE RAYGAME_TESTLIB_GTEST)
        target_link_libraries(${_target} PUBLIC GTest::gtest)
    endif()
endfunction()

function(raygame_add_test _target)
    if(RAYGAME_TESTLIB STREQUAL "DOCTEST")
        target_compile_definitions(${_target} PRIVATE RAYGAME_TESTLIB_DOCTEST)
        target_include_directories(${_target} PUBLIC ${DOCTEST_INCLUDE_DIR})
        doctest_discover_tests(${_target})
    elseif(RAYGAME_TESTLIB STREQUAL "GTEST")
        target_compile_definitions(${_target} PRIVATE RAYGAME_TESTLIB_GTEST)
        target_include_directories(${_target} PUBLIC ${GTEST_INCLUDE_DIR})
        gtest_discover_tests(${_target})
    endif()
endfunction()
