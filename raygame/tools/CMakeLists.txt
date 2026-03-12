find_package(PNG)

raygame_bin(
    resmk
    SRCS resmk/main.cpp resmk/resources/resource.cpp resmk/resources/png.cpp
    DEPS RayGame::Core RayGame::External::STB::Image
)
set(RAYGAME_RESMK_EXE ${CMAKE_CURRENT_BINARY_DIR}/resmk)
add_executable(RayGame::Tools::ResMk ALIAS resmk)
