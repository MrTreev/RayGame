#!/bin/sh
# shellcheck enable=require-variable-braces

case "${BUILD_LOG_LEVEL:-INFO}" in
    DEBUG) LOGSH_LEVEL=4 ;;
    INFO) LOGSH_LEVEL=3 ;;
    SUCCESS) LOGSH_LEVEL=2 ;;
    WARNING) LOGSH_LEVEL=1 ;;
    ERROR) LOGSH_LEVEL=0 ;;
esac
. "${PATH_SCRIPTS}/log.sh"

newer_than(){ [ "$(stat -c'%Y' "$1")" -gt "$(stat -c'%Y' "$2")" ] && return 0 || return 1; }
older_than(){ [ "$(stat -c'%Y' "$1")" -gt "$(stat -c'%Y' "$2")" ] && return 1 || return 0; }
