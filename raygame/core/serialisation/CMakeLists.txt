raygame_lib(
    RayGameCoreSerialisation
    HDRS serialisation.h
    SRCS serialisation.cpp
    DEPS RayGame::Core::Base
         RayGame::External::ZppBits
)
add_library(RayGame::Core::Serialisation ALIAS RayGameCoreSerialisation)
