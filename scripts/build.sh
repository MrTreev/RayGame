#!/bin/sh

log()      { printf "\033[34m%s\033[0m\n" "$@"; };
log_red()  { printf "\033[31m%s\033[0m\n" "$@"; };
log_green(){ printf "\033[32m%s\033[0m\n" "$@"; };

nonempty() {
    log_red 'ERROR: "%s" requires a non-empty option argument.\n' "$1" >&2;
    exit 1;
};

BUILD_DIR="${BUILD_DIR:-build}"
TOOLCHAIN="${TOOLCHAIN:-linux-clang-libcxx}"
EXPORT_COMPILE_COMMANDS="${EXPORT_COMPILE_COMMANDS:-ON}"

show_help(){
cat <<ENDHELP
    -h|--help                   Shows this message
    -c|--clean                  Clean builds before running
    --build-dir=dir             Set the build dir ${BUILD_DIR}
    --build-type=type           Set the build type (Debug,Release,RelWithDebInfo)
    --export-compile-commands   Export compile_commands.json
    --toolchain=toolchain       Set the toolchain ${TOOLCHAIN}
ENDHELP
};

while [ $# -gt 0 ]; do case $1 in

    -h|-\?|--help) show_help; exit ;;
    -c|--clean) CLEAN=1 ;;

    --build-dir) if [ -n "$2" ];then { BUILD_DIR=$2; shift; } else nonempty "--build-dir"; fi ;;
    --build-dir=?*) BUILD_DIR=${1#*=} ;;
    --build-dir=) nonempty "--build-dir" ;;

    --build-type) if [ -n "$2" ];then { BUILD_TYPE=$2; shift; } else nonempty "--build-type"; fi ;;
    --build-type=?*) BUILD_TYPE=${1#*=} ;;
    --build-type=) nonempty "--build-type" ;;

    --export-compile-commands) if [ -n "$2" ];then { EXPORT_COMPILE_COMMANDS=$2; shift; } else EXPORT_COMPILE_COMMANDS=ON; fi ;;
    --export-compile-commands=?*) EXPORT_COMPILE_COMMANDS=${1#*=} ;;
    --export-compile-commands=) nonempty "--export-compile-commands" ;;

    --toolchain) if [ -n "$2" ];then { TOOLCHAIN=$2; shift; } else nonempty "--toolchain"; fi ;;
    --toolchain=?*) TOOLCHAIN=${1#*=} ;;
    --toolchain=) nonempty "--toolchain" ;;

    -?*) log_red 'ERROR: Unknown option: %s\n' "$1" >&2; exit 1 ;;
esac;shift;done

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
            --toolchain "${TOOLCHAIN}" \
            -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
            -DCMAKE_EXPORT_COMPILE_COMMANDS="${EXPORT_COMPILE_COMMANDS}" \
            ;
    fi;
    command_result "$?" "Configure";
};

run_build(){
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
        ctest \
            --test-dir "${BUILD_DIR}" \
            --rerun-failed \
            --output-on-failure\
            ;
    fi
};

run_configure && run_build && run_test;
