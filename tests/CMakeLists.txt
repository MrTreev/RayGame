enable_testing()
find_package(doctest REQUIRED)
include(CTest)
include(DocTest)

raygame_lib(RayGameRayTest)
add_library(RayGame::RayTest ALIAS RayGameRayTest)
target_sources(RayGameRayTest
    PUBLIC
    raytest/test.h
    raytest/tests_begin.h
)

function(raygame_test _target)
    add_executable(${_target})
    target_compile_features(${_target} PUBLIC cxx_std_23)
    target_include_directories(${_target} PUBLIC
        $<BUILD_INTERFACE:${RayGame_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include/raygame>
    )
    set_target_properties(
        ${_target}
        PROPERTIES VERSION ${RayGame_VERSION}
                   CXX_VISIBILITY_PRESET hidden
                   CXX_STANDARD 23
                   CXX_STANDARD_REQUIRED YES
                   VISIBILITY_INLINES_HIDDEN YES
    )
    raygame_add_args(${_target})
    target_compile_definitions(${_target} PUBLIC "RAYGAME_LOG_${RAYGAME_LOG_LEVEL}")
    if(RAYGAME_LOG_DISABLE_SOURCE_LOCATION)
        target_compile_definitions(${_target} PUBLIC "RAYGAME_DISABLE_SOURCE_LOCATION")
    elseif(RAYGAME_BT_IS_DEBUG)
        target_compile_definitions(${_target} PUBLIC "RAYGAME_ENABLE_SOURCE_LOCATION")
    endif()
    target_include_directories(${_target} PUBLIC ${DOCTEST_INCLUDE_DIR})
    target_link_libraries(RayGameRayTest PUBLIC doctest::doctest)
    doctest_discover_tests(${_target})
endfunction()

add_subdirectory(core)
