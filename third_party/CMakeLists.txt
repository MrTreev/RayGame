FetchContent_Declare(
    zpp_bits
    GIT_REPOSITORY https://github.com/eyalz800/zpp_bits.git
    GIT_TAG e5ff2b23904cdca8778ab7284bf82257102c8022
)
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG f1c79c02822848a9bed4315b12c8c8f3761e1296
)
FetchContent_MakeAvailable(zpp_bits)
FetchContent_MakeAvailable(stb)

add_library(RayGameExternalZppBits INTERFACE)
target_include_directories(
    RayGameExternalZppBits INTERFACE $<BUILD_INTERFACE:${zpp_bits_SOURCE_DIR}> $<INSTALL_INTERFACE:include/zpp_bits>
)
add_library(RayGame::External::ZppBits ALIAS RayGameExternalZppBits)

function(stb_lib _target)
    set(options)
    set(oneValueArgs IMPLDEF HDRDEF PRELUDE)
    set(multiValueArgs FNAME DEFS)
    cmake_parse_arguments(RAYGAME_TESTARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    add_custom_command(
        OUTPUT ${RAYGAME_TESTARGS_FNAME}.c
        COMMAND printf "${RAYGAME_TESTARGS_PRELUDE}\\n#include <${RAYGAME_TESTARGS_FNAME}.h>" >
                ${RAYGAME_TESTARGS_FNAME}.c
        VERBATIM
    )
    add_library(RayGameExternalStb${_target})
    target_sources(
        RayGameExternalStb${_target}
        PUBLIC ${stb_SOURCE_DIR}/${RAYGAME_TESTARGS_FNAME}.h
        PRIVATE ${RAYGAME_TESTARGS_FNAME}.c
    )
    set_target_properties(
        RayGameExternalStb${_target}
        PROPERTIES C_VISIBILITY_PRESET hidden
                   C_STANDARD 23
                   C_STANDARD_REQUIRED YES
                   LINKER_LANGUAGE C
                   VISIBILITY_INLINES_HIDDEN YES
    )
    target_compile_definitions(
        RayGameExternalStb${_target}
        PUBLIC ${RAYGAME_TESTARGS_HDRDEF} ${RAYGAME_TESTARGS_DEFS}
        PRIVATE ${RAYGAME_TESTARGS_IMPLDEF}
    )
    target_compile_options(RayGameExternalStb${_target} PRIVATE -w -Wno-tautological-comprare)
    target_include_directories(RayGameExternalStb${_target} PUBLIC ${stb_SOURCE_DIR})
    add_library(RayGame::External::STB::${_target} ALIAS RayGameExternalStb${_target})
endfunction()

stb_lib(CLexer IMPLDEF STB_C_LEXER_IMPLEMENTATION FNAME stb_c_lexer)
stb_lib(Include IMPLDEF STB_INCLUDE_IMPLEMENTATION FNAME stb_include)
stb_lib(LeakCheck IMPLDEF STB_LEAKCHECK_IMPLEMENTATION FNAME stb_leakcheck)
stb_lib(Sprintf IMPLDEF STB_SPRINTF_IMPLEMENTATION FNAME stb_sprintf)

stb_lib(HexWave IMPLDEF STB_HEXWAVE_IMPLEMENTATION FNAME stb_hexwave)
stb_lib(Perlin IMPLDEF STB_PERLIN_IMPLEMENTATION FNAME stb_perlin)
stb_lib(RectPack IMPLDEF STB_RECT_PACK_IMPLEMENTATION FNAME stb_rect_pack)
stb_lib(TrueType IMPLDEF STB_TRUETYPE_IMPLEMENTATION FNAME stb_truetype)

stb_lib(Image IMPLDEF STB_IMAGE_IMPLEMENTATION FNAME stb_image)
stb_lib(ImageResize IMPLDEF STB_IMAGE_RESIZE_IMPLEMENTATION FNAME stb_image_resize2)
stb_lib(ImageWrite IMPLDEF STB_IMAGE_WRITE_IMPLEMENTATION FNAME stb_image_write)

stb_lib(EasyFont FNAME stb_easy_font)
