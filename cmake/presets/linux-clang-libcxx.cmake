set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86)

set(triple x86_64-linux-gnu)
set(tools /usr)

set(CMAKE_C_COMPILER ${tools}/bin/clang)
set(CMAKE_C_COMPILER_AR ${tools}/bin/llvm-ar)
set(CMAKE_C_COMPILER_CLANG_SCAN_DEPS ${tools}/bin/clang-scan-deps)
set(CMAKE_C_COMPILER_TARGET ${triple})

set(CMAKE_CXX_COMPILER ${tools}/bin/clang++)
set(CMAKE_CXX_COMPILER_AR ${tools}/bin/llvm-ar)
set(CMAKE_CXX_COMPILER_TARGET ${triple})

set(CMAKE_ADDR2LINE ${tools}/bin/llvm-addr2line)
set(CMAKE_DLLTOOL ${tools}/bin/llvm-dlltool)
set(CMAKE_READELF ${tools}/bin/llvm-readelf)
set(CMAKE_STRIP ${tools}/bin/llvm-strip)

set(COVERAGE_COMMAND ${tools}/bin/lcov)
set(COVERAGE_EXTRA_FLAGS -l)

set(CMAKE_LINKER ${tools}/bin/ld.lld)
set(CMAKE_NM ${tools}/bin/llvm-nm)
set(CMAKE_OBJCOPY ${tools}/bin/llvm-objcopy)
set(CMAKE_OBJDUMP ${tools}/bin/llvm-objdump)
set(CMAKE_RANLIB ${tools}/bin/llvm-ranlib)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

add_compile_options(-Wno-unused-command-line-argument)
add_compile_options(-stdlib=libc++)
add_link_options(-stdlib=libc++)
