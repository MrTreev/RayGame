raygame_lib(
    RayGameCoreSerialisation
    HDRS serialisation.h
    SRCS serialisation.cpp
    DEPS RayGame::Core::Base
)
target_link_libraries(RayGameCoreSerialisation PUBLIC RayGame::External::ZppBits)
add_library(RayGame::Core::Serialisation ALIAS RayGameCoreSerialisation)
