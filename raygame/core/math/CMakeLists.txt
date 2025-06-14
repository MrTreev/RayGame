raygame_lib(
    RayGameCoreMath
    HDRS arithmetic/safe_add.h
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
    SRCS arithmetic/safe_add.cpp
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
    DEPS RayGame::Core::Base
)
add_library(RayGame::Core::Math ALIAS RayGameCoreMath)
