#!/bin/sh
set -e

WHICH_BUILD_LIST=TWO
unset CLEAN
unset FRESH

log()      { printf "\033[34m%s\033[0m\n" "$@"; };
log_red()  { printf "\033[31m%s\033[0m\n" "$@"; };
log_green(){ printf "\033[32m%s\033[0m\n" "$@"; };

show_help(){
cat <<ENDHELP
    -h|--help                   Shows this message
    -c|--clean                  Clean builds before running
    -f|--full                   Build ALL types (very slow)
    -r|--release                Build only release
    --set-type <fullname>       Set build for clangd to follow
ENDHELP
};

while [ $# -gt 0 ]; do case $1 in
    -h|-\?|--help) show_help; exit ;;
    -c|--clean) CLEAN=1 ;;
    -f|--fresh) FRESH=1 ;;

    --full) WHICH_BUILD_LIST=FULL ;;
    --release) WHICH_BUILD_LIST=RELEASE ;;
    --all) WHICH_BUILD_LIST=ALL ;;

    --set-type) if [ -n "$2" ];then { SET_TYPE=$2; shift; } else nonempty "--set-type"; fi ;;
    --set-type=?*) SET_TYPE=${1#*=} ;;
    --set-type=) nonempty "--set-type" ;;

    -?*) log_red 'ERROR: Unknown option: %s\n' "$1" >&2; exit 1 ;;
esac;shift;done

if [ -n "${SET_TYPE:-}" ]; then
    log_green "Setting build fullname: \"${SET_TYPE}\"";
    rm compile_commands.json;
    ln -s "build-multi/${SET_TYPE}/compile_commands.json" compile_commands.json;
    rm -rf .cache/clangd;
    log_green "Build set, exiting";
    exit 0;
fi;
if [ "${1:-}" = "clean" ]; then export CLEAN=1; fi;


case "${WHICH_BUILD_LIST}" in
    ALL)        BUILD_LIST='Debug RelWithDebInfo' ;;
    FULL)       BUILD_LIST='Debug Release RelWithDebInfo MinSizeRel' ;;
    TWO)        BUILD_LIST='Debug RelWithDebInfo' ;;
    RELEASE)    BUILD_LIST='RelWithDebInfo' ;;
    *) log_red "ERROR: Unknown build list type: ${WHICH_BUILD_LIST}"; exit 1;;
esac

if [ "${WHICH_BUILD_LIST}" != "ALL" ]; then
    for toolchain in toolchain/presets/*.cmake; do
        for build_type in ${BUILD_LIST}; do
            tcname="${toolchain##*/}"
            fullname="${tcname%%.cmake}-${build_type}"
            log "Running build for \"${fullname}\""
            "${0%%_multi.sh}.sh" \
                ${CLEAN:+--clean} \
                ${FRESH:+--fresh} \
                --build-dir="build-multi/${fullname}" \
                --build-type="${build_type}" \
                --export-compile-commands="${EXPORT_COMPILE_COMMANDS:-ON}" \
                --toolchain="${toolchain}" \
                ;
        done;
    done;
else
    for time_frames in 'ON' 'OFF'; do
    for math_random_full in 'ON' 'OFF'; do
    for log_level in 'TRACE' 'DEBUG' 'INFO' 'WARNING' 'ERROR' 'FATAL'; do
    for source_location in 'FULL' 'BASE' 'NONE'; do
    for toolchain in toolchain/presets/*.cmake; do
        for build_type in ${BUILD_LIST}; do
            tcname="${toolchain##*/}"
            fullname="all-${tcname%%.cmake}-${time_frames}-${math_random_full}-${source_location}-${log_level}-${build_type}"
            log "Running build for \"${fullname}\""
            "${0%%_multi.sh}.sh" \
                ${CLEAN:+--clean} \
                ${FRESH:+--fresh} \
                --build-dir="build-multi/${fullname}" \
                --build-type="${build_type}" \
                --export-compile-commands="${EXPORT_COMPILE_COMMANDS:-ON}" \
                --toolchain="${toolchain}" \
                -- \
                -DRAYGAME_BUILD_TESTS=ON \
                -DRAYGAME_BUILD_DOCS=ON \
                -DRAYGAME_BUILD_GAMES=ON \
                -DRAYGAME_LOG_LEVEL="${log_level}" \
                -DRAYGAME_SOURCE_LOCATION=${source_location} \
                -DRAYGAME_MATH_RANDOM_FULL=${math_random_full} \
                -DRAYGAME_TIME_FRAMES=${time_frames} \
                ;
        done;
    done;done;done;done;done;
fi
