raygame_lib(
    RayGameCoreBase
    HDRS concepts.h
         condition.h
         config.h
         debug.h
         exception.h
         logger.h
         matrix.h
         types.h
    SRCS concepts.cpp
         condition.cpp
         config.cpp
         debug.cpp
         exception.cpp
         logger.cpp
         matrix.cpp
         types.cpp
)
add_library(RayGame::Core::Base ALIAS RayGameCoreBase)

add_subdirectory(drawing)
add_subdirectory(math)
add_subdirectory(window)
add_subdirectory(io)
add_subdirectory(serialisation)
