raygame_resource(
    GeneratedPngImage
    NAME generated_png_image
    RESOURCES pngtest.png
)
raygame_bin(
    GeneratedImage
    SRCS main.cpp
    DEPS RayGame::Core GeneratedPngImage
)
