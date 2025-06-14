raygame_lib(
    RayGameCoreIo
    HDRS file.h
    SRCS file.cpp
)
add_library(RayGame::Core::Io ALIAS RayGameCoreIo)

