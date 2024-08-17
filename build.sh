#!/bin/sh

set -eu

RG_LOG_LEVEL="${RG_LOG_LEVEL:-INFO}"
CXX="${CXX:-clang++}"
LD="${LD:-lld}"
unset CFLAGS
unset CXXFLAGS

. config.sh


