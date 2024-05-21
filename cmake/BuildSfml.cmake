# SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
set_property(
	DIRECTORY ${SFML_SOURCE_DIR}
    APPEND
	PROPERTY COMPILE_OPTIONS -Wno-error -Wno-zero-as-null-pointer-constant
)

