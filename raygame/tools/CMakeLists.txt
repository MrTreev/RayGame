find_package(PNG)

raygame_bin(
    resmk
    SRCS resmk.cpp
    DEPS RayGame::Core RayGame::External::STB::Image
)
