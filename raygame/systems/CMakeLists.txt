raygame_lib(
    RayGameSystems
    HDRS core/name.h core/sex.h
    SRCS core/name.cpp
    DEPS
)
add_library(RayGame::Systems ALIAS RayGameSystems)
