#!/bin/sh
# shellcheck source-path=bin/scripts
# shellcheck enable=require-variable-braces
set -eu

EXECUTABLE="RayGame"
RG_LOG_LEVEL="${RG_LOG_LEVEL:-INFO}"
BUILD_TYPE="${BUILD_TYPE:-DEBUG}"
COMPILER="${COMPILER:-clang}"
LINKER="${LINKER:-lld}"
STEPPED_BUILD="NO"
CXXSTD="c++23"

PATH_BIN="${PWD}/bin"
PATH_OUT="${PWD}/out"
PATH_SRC="${PWD}/src"
PATH_ETC="${PWD}/etc"
PATH_INC="${PATH_OUT}/include"
PATH_LIB="${PATH_OUT}/lib"
PATH_BLD="${PATH_OUT}/build"
PATH_SCRIPTS="${PATH_BIN}/scripts"
PATH_WAYLAND_XML="${PATH_ETC}/wayland-protocols"
BUILD_LOG_LEVEL="DEBUG"
. "${PATH_SCRIPTS}/util.sh"

FILE_CONFIG="${PATH_SCRIPTS}/config.sh"
# shellcheck source=config.sh
. "${FILE_CONFIG}"
update_flags

wayland_xml="$(find "${PATH_WAYLAND_XML}" -type f -iname '*.xml')"
core_srcs="$(find "${PATH_SRC}/core" -type f -iname '*.cpp')"
system_srcs="$(find "${PATH_SRC}/system" -type f -iname '*.cpp')"
world_srcs="$(find "${PATH_SRC}/world" -type f -iname '*.cpp')"

for xmlfile in ${wayland_xml}; do
	generate_wayland "${xmlfile}"
done
compile_wayland "${PATH_LIB}/libraygame_wayland.so"

for srcfile in ${core_srcs}; do
	compile "${srcfile}"
done

core_objs="$(objfile "${core_srcs}")"

compile "${PATH_SRC}/main.cpp"
${LD} ${LDFLAGS} -L"${PATH_LIB}" -lraygame_wayland -o "${FILE_EXE}" "${PATH_BLD}/main.o" ${core_objs}

generate_compile_commands
