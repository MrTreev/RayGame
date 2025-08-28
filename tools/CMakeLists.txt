find_package(PNG)

raygame_bin(
    resmk
    SRCS raygame_resource.cpp
    DEPS RayGame::Core PNG::PNG
)
