add_library(Core)
add_library(RayGame::Core ALIAS Core)
target_include_directories(Core PUBLIC ${RG_PATH_SRC})
target_compile_features(Core PUBLIC cxx_std_23)
target_link_libraries(Core PRIVATE)
set_target_properties(
    Core
    PROPERTIES VERSION ${PROJECT_VERSION}
               CXX_VISIBILITY_PRESET hidden
			   CXX_STANDARD 23
               VISIBILITY_INLINES_HIDDEN YES
)
target_compile_definitions(Core PUBLIC "RAYGAME_LOG_${RG_LOG_LEVEL}")
target_sources(
    Core
    PUBLIC colours.h
           condition.h
           config.h
           debug.h
           exception.h
           image.h
           logger.h
           math.h
           pixel.h
           spritesheet.h
           texture.h
           types.h
           window.h
    PRIVATE colours.cpp
            condition.cpp
            config.cpp
            debug.cpp
            exception.cpp
            image.cpp
            logger.cpp
            math.cpp
            pixel.cpp
            spritesheet.cpp
            texture.cpp
            types.cpp
            window.cpp
)
add_subdirectory(windowimpl)

if(RG_ENABLE_WAYLAND)
    include(RgWayland)
    rg_target_client_protocol(TARGET Core PROTOCOLS wayland xdg-shell)
endif()
