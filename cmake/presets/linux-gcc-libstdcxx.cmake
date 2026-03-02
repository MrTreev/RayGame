set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86)

set(triple x86_64-linux-gnu)
set(tools ${CMAKE_CURRENT_LIST_DIR}/../../toolchains/gcc)

set(CMAKE_C_COMPILER ${tools}/bin/gcc)
set(CMAKE_C_COMPILER_AR ${tools}/bin/gcc-ar)
set(CMAKE_C_COMPILER_TARGET ${triple})

set(CMAKE_CXX_COMPILER ${tools}/bin/g++)
set(CMAKE_CXX_COMPILER_AR ${tools}/bin/gcc-ar)
set(CMAKE_CXX_COMPILER_TARGET ${triple})

set(CMAKE_ADDR2LINE ${tools}/bin/addr2line)
set(CMAKE_DLLTOOL ${tools}/bin/dlltool)
set(CMAKE_READELF ${tools}/bin/readelf)
set(CMAKE_STRIP ${tools}/bin/strip)

set(COVERAGE_COMMAND ${tools}/bin/gcov)
set(COVERAGE_EXTRA_FLAGS -l)

set(CMAKE_LINKER ${tools}/bin/ld.gold)
set(CMAKE_NM ${tools}/bin/gcc-nm)
set(CMAKE_OBJCOPY ${tools}/bin/objcopy)
set(CMAKE_OBJDUMP ${tools}/bin/objdump)
set(CMAKE_RANLIB ${tools}/bin/gcc-ranlib)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CXX_SCAN_FOR_MODULES OFF)

add_link_options(-static-libstdc++)
