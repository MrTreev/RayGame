#!/bin/sh

run_configure(){
    cmake \
        -B build \
        -S . \
        -G Ninja \
        --toolchain ./cmake/presets/linux-clang-libcxx.cmake \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
        ;
};

run_build(){
    cmake \
        --build build \
        ;
};

run_test(){
    ctest \
        --test-dir build \
        --quiet \
        ;
};

run_configure && run_build && run_test;

unset -f run_configure run_build run_test
