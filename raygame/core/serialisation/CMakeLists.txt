raygame_lib(
    RayGameCoreSerialisation
    HEADERS serialisation.h
    SOURCES serialisation.cpp
    DEPENDS RayGame::Core::Base RayGame::External::ZppBits
)
