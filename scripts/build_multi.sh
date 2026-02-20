#!/bin/sh
set -e

WHICH_BUILD_LIST=TWO

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
    -f|--full) WHICH_BUILD_LIST=FULL ;;
    -r|--release) WHICH_BUILD_LIST=RELEASE ;;

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
    FULL)       BUILD_LIST='Debug Release RelWithDebInfo MinSizeRel' ;;
    TWO)        BUILD_LIST='Debug RelWithDebInfo' ;;
    RELEASE)    BUILD_LIST='RelWithDebInfo' ;;
    *) log_red "ERROR: Unknown build list type: ${WHICH_BUILD_LIST}"; exit 1;;
esac

for toolchain in cmake/presets/*.cmake; do
    for build_type in ${BUILD_LIST}; do
        tcname="${toolchain##*/}"
        fullname="${tcname%%.cmake}-${build_type}"
        log "Running build for \"${fullname}\""
        "${0%%_multi.sh}.sh" \
            ${CLEAN:+--clean} \
            --build-dir="build-multi/${tcname%%.cmake}-${build_type}" \
            --build-type="${build_type}" \
            --export-compile-commands="${EXPORT_COMPILE_COMMANDS:-ON}" \
            --toolchain="${toolchain}" \
            ;
    done;
done;
