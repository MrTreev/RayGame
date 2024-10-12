include(RgResources)
add_executable(Game)
target_link_libraries(Game PRIVATE Core)
target_sources(Game PUBLIC main.cpp)
rg_add_args(Game)

if(RG_RUN_GAME)
    add_custom_target(
        RunGame ALL
        COMMAND Game
        DEPENDS Game
        VERBATIM
    )
endif()
