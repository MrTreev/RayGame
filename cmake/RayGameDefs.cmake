include_guard()
include(RayGameSetup)

function(raygame_add_defs _target)
    target_compile_definitions(${_target} PUBLIC "RAYGAME_LOG_${RAYGAME_LOG_LEVEL}")
    target_compile_definitions(${_target} PUBLIC "RAYGAME_SOURCE_LOCATION_${RAYGAME_SOURCE_LOCATION}")
endfunction()
