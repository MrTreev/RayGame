include(FetchContent)
FetchContent_Declare(
    RAYLIB GIT_REPOSITORY https://github.com/MrTreev/raylib.git GIT_TAG 5.0
    SYSTEM
)

FetchContent_MakeAvailable(RAYLIB)

set_property(
    DIRECTORY ${raylib_SOURCE_DIR}
    APPEND
    PROPERTY COMPILE_OPTIONS -Wno-error -Wno-zero-as-null-pointer-constant -Wno-implicit-const-int-float-conversion
)
