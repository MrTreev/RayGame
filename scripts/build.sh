#!/bin/sh

run_configure(){
    cmake \
        -B build \
        -S . \
        -G Ninja \
        --toolchain ./cmake/presets/linux-clang-libcxx.cmake \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
        -DRAYGAME_LOG_DISABLE_SOURCE_LOCATION=ON \
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
