get_target_property(RESMK_EXE RayGame::Tools::ResMk BINARY_DIR)
raygame_test(Resmk
    SRCS resmk.cpp
    DEPS RayGame::Core
    DEFS
        RESMK="${RESMK_EXE}/resmk"
        RESMK_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data"
        RESMK_FILE_DIR="${CMAKE_CURRENT_BINARY_DIR}/data"
)
