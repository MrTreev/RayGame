raygame_lib(RayGameCoreMath)
add_library(RayGame::Core::Math ALIAS RayGameCoreMath)
target_sources(
    RayGameCoreMath
    PUBLIC arithmetic/safe_add.h
           arithmetic/safe_div.h
           arithmetic/safe_mult.h
           arithmetic/safe_sub.h
           arithmetic.h
           math.h
           mathrule.h
           numeric_cast.h
           random.h
           rect.h
           ring_average.h
           vector.h
    PRIVATE arithmetic/safe_add.cpp
            arithmetic/safe_div.cpp
            arithmetic/safe_mult.cpp
            arithmetic/safe_sub.cpp
            arithmetic.cpp
            math.cpp
            mathrule.cpp
            numeric_cast.cpp
            random.cpp
            rect.cpp
            ring_average.cpp
            vector.cpp
)
target_link_libraries(RayGameCoreMath PUBLIC RayGame::Core::Base)
