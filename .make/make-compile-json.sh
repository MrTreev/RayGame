#!/bin/sh

make "$@" --always-make --dry-run \
 | grep -wE '[gt]?cc|[gc]\+\+|c[0-9]{2}|clang|clang\+\+' \
 | grep -w '\-c' \
 | jq -nR '[inputs|{directory:".", command:., file: match(" [^ ]+$").string[1:]}]' \
 > compile_commands.json
