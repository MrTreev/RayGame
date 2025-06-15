add_library(RayGameExternalZppBits)
target_sources(
    RayGameExternalZppBits
    PUBLIC include/zppbits.h
    PRIVATE zpp_bits/zpp_bits.h include/zppbits.cpp
)
target_include_directories(
    RayGameExternalZppBits
    PUBLIC $<BUILD_INTERFACE:${RayGame_SOURCE_DIR}/third_party/include>
           $<INSTALL_INTERFACE:include/third_party>
           $<BUILD_INTERFACE:${RayGame_SOURCE_DIR}/third_party/zpp_bits>
           $<INSTALL_INTERFACE:include/zpp_bits>
)
set_target_properties(
    RayGameExternalZppBits
    PROPERTIES CXX_VISIBILITY_PRESET hidden
               CXX_STANDARD 23
               CXX_STANDARD_REQUIRED YES
               VISIBILITY_INLINES_HIDDEN YES
)
add_library(RayGame::External::ZppBits ALIAS RayGameExternalZppBits)

add_subdirectory(glfw)
find_package(OpenGL)

add_library(RayGameExternalImgui)
target_sources(
    RayGameExternalImgui
    PUBLIC imgui/imgui.h
           imgui/backends/imgui_impl_glfw.h
           imgui/backends/imgui_impl_opengl3.h
    PRIVATE
            imgui/imconfig.h
            imgui/imgui_internal.h
            imgui/imstb_rectpack.h
            imgui/imstb_textedit.h
            imgui/imstb_truetype.h
            imgui/imgui.cpp
            imgui/imgui_draw.cpp
            imgui/imgui_tables.cpp
            imgui/imgui_widgets.cpp
            imgui/backends/imgui_impl_glfw.cpp
            imgui/backends/imgui_impl_opengl3.cpp
)
target_link_libraries(
    RayGameExternalImgui
    PUBLIC glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES}
)
target_include_directories(
    RayGameExternalImgui
    PUBLIC ${RayGame_SOURCE_DIR}/third_party/include
           ${RayGame_SOURCE_DIR}/third_party/imgui
           ${RayGame_SOURCE_DIR}/third_party/imgui/backends
           ${RayGame_SOURCE_DIR}/third_party/glfw/include
)
add_library(RayGame::External::Imgui ALIAS RayGameExternalImgui)
