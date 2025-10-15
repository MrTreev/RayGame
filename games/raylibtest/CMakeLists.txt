raygame_lib(
    RayLibTestImage
    HDRS test.h
    SRCS test.cpp
)
raygame_bin(
    RayLibTest
    SRCS main.cpp
    DEPS RayGame::Core RayLibTestImage RayGameWindowWayland
)
