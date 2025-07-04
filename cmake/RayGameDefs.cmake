include_guard()
include(RayGameSetup)

function(raygame_add_defs _target)
    target_compile_definitions(${_target} PUBLIC "RAYGAME_LOG_${RAYGAME_LOG_LEVEL}")
    if(RAYGAME_LOG_DISABLE_SOURCE_LOCATION)
        target_compile_definitions(${_target} PUBLIC "RAYGAME_DISABLE_SOURCE_LOCATION")
    elseif(RAYGAME_BT_IS_DEBUG)
        target_compile_definitions(${_target} PUBLIC "RAYGAME_ENABLE_SOURCE_LOCATION")
    endif()
endfunction()
