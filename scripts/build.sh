#!/bin/sh

if [ "${1:-}" = "clean" ]; then
    CLEAN=1
fi
BUILD_DIR="${BUILD_DIR:-build}"
BUILD_TYPE="${BUILD_TYPE:-Debug}"
EXPORT_COMPILE_COMMANDS="${EXPORT_COMPILE_COMMANDS:-ON}"
DISABLE_SOURCE_LOC="${DISABLE_SOURCE_LOC:-ON}"

log(){
    printf "\033[34m%s\033[0m\n" "$@";
};

log_red(){
    printf "\033[31m%s\033[0m\n" "$@";
};

log_green(){
    printf "\033[32m%s\033[0m\n" "$@";
};

command_result(){
    if [ "$1" -eq 0 ];then
        log_green "$2 Succeeded";
    else
        log_red "$2 Failed with $1";
    fi;
    return "$1";
};

run_configure(){
    if [ ! -d "${BUILD_DIR}" ]; then
        cmake \
            -B "${BUILD_DIR}" \
            -S . \
            -G Ninja \
            --toolchain ./cmake/presets/linux-clang-libcxx.cmake \
            -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
            -DCMAKE_EXPORT_COMPILE_COMMANDS="${EXPORT_COMPILE_COMMANDS}" \
            -DRAYGAME_LOG_DISABLE_SOURCE_LOCATION="${DISABLE_SOURCE_LOC}" \
            ;
    fi;
    command_result "$?" "Configure";
};

run_build(){
    set +x
    cmake \
        --build "${BUILD_DIR}" \
        ${CLEAN:+--clean-first} \
        ;
    command_result "$?" "Build";
};

run_test(){
    ctest \
        --test-dir "${BUILD_DIR}" \
        --quiet \
        ;
    result=$?;
    command_result "$result" "Tests";
    if [ "${result}" -ne 0 ]; then
        ctest --test-dir build --rerun-failed --output-on-failure;
    fi
};

run_configure && run_build && run_test;
