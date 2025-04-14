raygame_lib(RayGameCoreDrawing)
add_library(RayGame::Core::Drawing ALIAS RayGameCoreDrawing)
target_sources(
    RayGameCoreDrawing
    PUBLIC
        image.h
        pixel.h
    PRIVATE
        image.cpp
        pixel.cpp
)
