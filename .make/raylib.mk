.EXPORT_ALL_VARIABLES:

RAY_PATH ?= ext/raylib/src
PLATFORM ?= PLATFORM_DESKTOP
RAYLIB_LIBTYPE ?= SHARED
RAYLIB_INSTALL_PATH ?= ${LIB_PATH}
RAYLIB_H_INSTALL_PATH ?= ${INC_PATH}
RAYLIB_BUILD_MODE ?= ${BUILD_TYPE}
RAYLIB_CONFIG_FLAGS  ?= NONE
RAYLIB_MODULE_AUDIO  ?= TRUE
RAYLIB_MODULE_MODELS ?= TRUE
USE_WAYLAND_DISPLAY   ?= TRUE
