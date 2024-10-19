if(RG_LIBCPP)
    add_compile_options(-stdlib=libc++ -lc++abi)
    add_link_options(-stdlib=libc++ -lc++abi)
endif()

include(RgProjectArgs)

add_subdirectory(core)
add_subdirectory(game)
add_subdirectory(test)
