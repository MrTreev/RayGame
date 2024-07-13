macro(add_battery_embed target_name)
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        set(B_EMBED_SILENCE_DEVMODE_WARNING ON)
    else()
        set(B_PRODUCTION_MODE ON)
    endif()
    add_subdirectory(${RAYGAME_ETC}/battery-embed battery-embed)
endmacro()
