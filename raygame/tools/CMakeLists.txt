find_package(PNG)

raygame_bin(
    resmk
    SRCS resmk/main.cpp resmk/resources/resource.cpp resmk/resources/png.cpp
    DEPS RayGame::Core RayGame::External::STB::Image
)
