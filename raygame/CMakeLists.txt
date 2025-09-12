add_subdirectory(core)

raygame_lib(
    RayGameCore
    DEPS RayGame::Core::Base
         RayGame::Core::Io
         RayGame::Core::Math
         RayGame::Core::Window
)
add_library(RayGame::Core ALIAS RayGameCore)

add_subdirectory(tools)

# raygame_lib(RayGameSystems)
# add_library(RayGame::Systems ALIAS RayGameSystems)
# add_subdirectory(systems)

# raygame_lib(RayGameWorld)
# add_library(RayGame::World ALIAS RayGameWorld)
# add_subdirectory(world)
