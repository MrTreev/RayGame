raygame_lib(
    RayGameWorld
    HDRS world.h
    SRCS
    DEPS
)
add_library(RayGame::World ALIAS RayGameWorld)
