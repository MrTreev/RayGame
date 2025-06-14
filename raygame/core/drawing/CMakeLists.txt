raygame_lib(
    RayGameCoreDrawing
    HDRS image.h
         pixel.h
    SRCS image.cpp
         pixel.cpp
    DEPS RayGame::Core::Base
         RayGame::Core::Math
)
add_library(RayGame::Core::Drawing ALIAS RayGameCoreDrawing)
