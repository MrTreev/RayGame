find_package(PNG)

raygame_bin(
    resmk
    SRCS resmk/main.cpp
    DEPS RayGame::Core RayGame::External::STB::Image
)
