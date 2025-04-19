add_executable(InitOnly)
target_link_libraries(InitOnly PRIVATE RayGame::Core)
target_sources(InitOnly PUBLIC main.cpp)
raygame_add_args(InitOnly)
