#pragma once
#include "raygame/core/config.h"

#if defined(RAYGAME_CC_MSC)
#    pragma system_header
#endif
#if defined(RAYGAME_CC_CLANG)
#    pragma clang system_header
#endif
#if defined(RAYGAME_CC_GCC)
#    pragma GCC system_header
#endif
#include "imgui.h"              // IWYU pragma: export
#include "imgui_impl_glfw.h"    // IWYU pragma: export
#include "imgui_impl_opengl3.h" // IWYU pragma: export
#include <GLFW/glfw3.h>         // IWYU pragma: export
