add_executable(Image)
target_link_libraries(Image PRIVATE RayGame::Core)
target_sources(Image PUBLIC
    main.cpp
    icon.h
    icon.cpp
    defs.h
    cottage.h
)
raygame_add_args(Image)
