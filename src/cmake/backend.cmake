if(RAYGAME_BACKEND STREQUAL RAYLIB)
    target_compile_definitions(${PROJECT_NAME} PRIVATE "RAYGAME_BACKEND_RAYLIB")
    FetchContent_Declare(
        RAYLIB
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
        SYSTEM
    )
    FetchContent_MakeAvailable(RAYLIB)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

elseif(RAYGAME_BACKEND STREQUAL VULKAN)
    target_compile_definitions(${PROJECT_NAME} PRIVATE "RAYGAME_BACKEND_VULKAN")
    find_package(Vulkan)
    if(VULKAN_FOUND)
        if(NOT Vulkan_dxc_EXECUTABLE)
            find_program(
                Vulkan_dxc_EXECUTABLE NAMES dxc HINTS "$ENV{VULKAN_SDK}/Bin"
                                                      "$ENV{VULKAN_SDK}/bin"
            )
        endif()
        if(DEFINED Vulkan_dxc_EXECUTABLE)
            message(
                "Found DirectX Shader Compiler under ${Vulkan_dxc_EXECUTABLE}"
            )
        elseif()
            message(
                "Couldn't find DirectX Shader Compiler executable, make sure it is present in Vulkan SDK or add it manually via Vulkan_dxc_EXECUTABLE env variable"
            )
        endif()
    else()
        message("VULKAN_SDK path not found, HLSL shaders won't be compiled")
    endif()
    # globally add VKB_DEBUG for the debug build
    add_compile_definitions($<$<CONFIG:DEBUG>:VKB_DEBUG>)
elseif(RAYGAME_BACKEND STREQUAL SDL)
    target_compile_definitions(${PROJECT_NAME} PRIVATE "RAYGAME_BACKEND_SDL")
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
endif()
