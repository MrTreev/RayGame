#!/bin/sh

cmake -B build -S . -G Ninja --toolchain ./cmake/presets/linux-clang-libcxx.cmake
cmake --build build
ctest --test-dir build
