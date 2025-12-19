#!/bin/sh
set -e

SOURCE_DIR="$(dirname -- "$(readlink "$0")")"
BUILDS_DIR="${SOURCE_DIR}/build-multi"
RUN_FULL=1

runfull(){ return $RUN_FULL; }


configure_preset_type(){
    preset="$1"
    build_type="$2"
    printf "Configuring: %s-%s\t" "${preset##*/}" "${build_type}"
    cmake \
        -S "${SOURCE_DIR}" \
        -G Ninja \
        -B "${BUILDS_DIR}/${preset##*/}-${build_type}" \
        --toolchain "${preset}.cmake" \
        -DCMAKE_BUILD_TYPE="${build_type}" \
        -DCMAKE_COMPILE_WARNING_AS_ERROR=ON >/dev/null\
        && echo "Succeeded" || echo "Failed"
}

build_preset_type(){
    preset="$1"; build_type="$2";
    printf "Building: %s-%s\t" "${preset##*/}" "${build_type}"
    cmake \
        --build "${BUILDS_DIR}/${preset##*/}-${build_type}" >/dev/null \
        && echo "Succeeded" || echo "Failed"
}

test_preset_type(){
    preset="$1"; build_type="$2";
    printf "Testing: %s-%s\t" "${preset##*/}" "${build_type}"
    ctest \
        --test-dir "${BUILDS_DIR}/${preset##*/}-${build_type}" \
        --quiet \
        && echo "Succeeded" || echo "Failed"
}

run_test(){
    for preset_file in "${SOURCE_DIR}/cmake/presets"/*.cmake; do
        preset="${preset_file%.cmake}"
        test_preset_type "${preset}" Debug
        test_preset_type "${preset}" RelWithDebInfo
        if runfull; then
            test_preset_type "${preset}" Release
            test_preset_type "${preset}" MinSizeRel
        fi
    done
}

run_build(){
    for preset_file in "${SOURCE_DIR}/cmake/presets"/*.cmake; do
        preset="${preset_file%.cmake}"
        build_preset_type "${preset}" Debug
        build_preset_type "${preset}" RelWithDebInfo
        if runfull; then
            build_preset_type "${preset}" Release
            build_preset_type "${preset}" MinSizeRel
        fi
    done
}

run_configure(){
    for preset_file in "${SOURCE_DIR}/cmake/presets"/*.cmake; do
        preset="${preset_file%.cmake}"
        configure_preset_type "${preset}" Debug
        configure_preset_type "${preset}" RelWithDebInfo
        if runfull; then
            configure_preset_type "${preset}" Release
            configure_preset_type "${preset}" MinSizeRel
        fi
    done
}

[ -n "${1:-}" ] || { echo "ERROR: No stage supplied" && exit 1; }
[ -z "${2:-}" ] || RUN_FULL=0

case "$1" in
    build) run_build ;;
    configure) run_configure ;;
    test) run_test ;;
    *) echo "ERROR: Invalid stage '$1'"; exit 1 ;;
esac
