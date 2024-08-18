#!/bin/sh
# shellcheck enable=require-variable-braces

FILE_CXXFLAGS="${FILE_CXXFLAGS:-${PATH_OUT}/CXXFLAGS}"
FILE_LDFLAGS="${FILE_LDFLAGS:-${PATH_OUT}/LDFLAGS}"
FILE_INCFLAGS="${FILE_INCFLAGS:-${PATH_OUT}/INCFLAGS}"
FILE_RAW_COMPILE_COMMANDS="${PATH_OUT}/compile_commands.txt"
FILE_EXE="${PATH_OUT}/${EXECUTABLE}"

cxxflags(){ tee -a "${FILE_CXXFLAGS}" >/dev/null && loginfo "Added ${1} to compiler flags"; }
ldflags(){ tee -a "${FILE_LDFLAGS}" >/dev/null && loginfo "Added ${1} to linker flags"; }
both_flags(){ tee -a "${FILE_CXXFLAGS}" | tee -a "${FILE_LDFLAGS}" >/dev/null && loginfo "Added ${1} to both flag sets"; }

case "${COMPILER}" in
	gcc)
		CXX=g++
		CC=gcc
		;;
	clang)
		CXX=clang++
		CC=clang
		;;
esac

case "${LINKER}" in
	gold) LD=ld.gold ;;
	lld) LD=ld.lld ;;
esac

export CXX
export CC
export LD

update_flags(){
	if older_than "${FILE_LDFLAGS}"  "${FILE_CONFIG}" \
	|| older_than "${FILE_CXXFLAGS}" "${FILE_CONFIG}" \
	|| older_than "${FILE_INCFLAGS}" "${FILE_CONFIG}"
	then

		mkdir -p "$(dirname "${FILE_CXXFLAGS}")"
		mkdir -p "$(dirname "${FILE_LDFLAGS}")"
		mkdir -p "$(dirname "${FILE_INCFLAGS}")"

		printf "" > "${FILE_CXXFLAGS}"
		printf "" > "${FILE_LDFLAGS}"
		printf "" > "${FILE_INCFLAGS}"

		if [ "${COMPILER}" = "gcc" ] || [ "${COMPILER}" = "clang" ]; then
			echo "-iquote${PATH_SRC}" >> "${FILE_INCFLAGS}"
			echo "-isystem${PATH_INC}" >> "${FILE_INCFLAGS}"
		else
			echo "-I${PATH_SRC}" >> "${FILE_INCFLAGS}"
		fi
		echo "-DRAYGAME_LOG_${RG_LOG_LEVEL}" | cxxflags "Raygame log level"
		echo "-DRAYGAME_LOG_LOCATION" | cxxflags "Raygame log source"

		cat <<-END_COMMON_FLAGS | cxxflags "Common build flags"
		-std=${CXXSTD}
		END_COMMON_FLAGS

		if [ "${COMPILER}" = "gcc" ]; then
			cat <<-END_GCC_WARNINGS | cxxflags "GCC warnings"
			-Wall
			-Wextra
			-Wshadow
			-Wdeprecated
			-Wabi
			-Wcast-align
			-Wconversion
			-Wdouble-promotion
			-Wduplicated-branches
			-Wduplicated-cond
			-Weffc++
			-Wformat-zero-length
			-Wformat=2
			-Wframe-address
			-Wimplicit
			-Wimplicit-fallthrough
			-Wimplicit-function-declaration
			-Wimplicit-int
			-Wimplicit-interface
			-Wimplicit-procedure
			-Winfinite-recursion
			-Wint-in-bool-context
			-Wlogical-op
			-Wmisleading-indentation
			-Wmissing-braces
			-Wnon-virtual-dtor
			-Wnull-dereference
			-Wold-style-cast
			-Woverloaded-virtual
			-Wpedantic
			-Wpointer-arith
			-Wrange-loop-construct
			-Wredundant-move
			-Wsign-compare
			-Wsign-conversion
			-Wsuggest-override
			-Wtautological-compare
			-Wundef
			-Wunused
			-Wuseless-cast
			-Wvariadic-macros
			-Wvla
			-Wzero-as-null-pointer-constant
			-Wzero-length-array
			END_GCC_WARNINGS
		fi

		if [ "${COMPILER}" = "clang" ]; then
			cat <<-END_CLANG_WARNINGS | cxxflags "Clang warnings"
			-Weverything
			-Wno-unused-command-line-argument
			-Wno-c++98-compat
			-Wno-c++98-compat-pedantic
			-Wno-c++-compat
			END_CLANG_WARNINGS

			cat <<-END_CLANG_ARGS | cxxflags "Clang flags"
			-fcolor-diagnostics
			END_CLANG_ARGS
		fi

		if [ "${COMPILER}" = "gcc" ]; then
			cat <<-END_GCC_ARGS | cxxflags "GCC Flags"
			-fdiagnostics-color=always
			END_GCC_ARGS
		fi

		if [ "${BUILD_TYPE:-OPT}" = "DEBUG" ]; then
			cat <<-END_DEBUG_ARGS | cxxflags "Debug flags"
			-Og
			-ggdb
			-fno-omit-frame-pointer
			END_DEBUG_ARGS
		else
			cat <<-END_OPT_ARGS | cxxflags "Optimisation flags"
			-Ofast
			END_OPT_ARGS
		fi

		if [ "${SANITIZE_ADDRESS:-NO}" = "YES" ]; then
			cat <<-END_SANITIZE_ADDRESS_ARGS | cxxflags "ASan flags"
			-fno-omit-frame-pointer
			-fsanitize=address
			-fsanitize-address-use-after-return=always
			-fsanitize-address-use-after-scope
			END_SANITIZE_ADDRESS_ARGS
		fi

		if [ "${SANITIZE_MEMORY:-NO}" = "YES" ]; then
			cat <<-END_SANITIZE_MEMORY_ARGS | cxxflags "MSan flags"
			-fno-omit-frame-pointer
			-fsanitize=memory
			END_SANITIZE_MEMORY_ARGS
		fi

		if [ "${SANITIZE_UNDEFINED_BEHAVIOUR:-NO}" = "YES" ]; then
			cat <<-END_SANITIZE_UNDEFINED_BEHAVIOUR_ARGS | cxxflags "UBSan flags"
			-fno-omit-frame-pointer
			-fsanitize=undefined
			-fsanitize=local-bounds
			-fsanitize=float-divide-by-zero
			-fsanitize=implicit-conversion
			-fsanitize=nullability
			END_SANITIZE_UNDEFINED_BEHAVIOUR_ARGS
		fi
	fi

	if [ "${LINKER}" = "lld" ]; then
		cat <<-END_LLD_ARGS | ldflags "LLD linker flags"
		--color-diagnostics
		--gdb-index
		END_LLD_ARGS
		if [ "${BUILD_TYPE:-OPT}" = "DEBUG" ]; then
			cat <<-END_LLD_DEBUG_ARGS | ldflags "LLD Debug flags"
			--demangle
			--icf=none
			--error-limit=0
			END_LLD_DEBUG_ARGS
		else
			cat <<-END_LLD_OPT_ARGS | ldflags "LLD Optimisation flags"
			--strip-all
			--discard-all
			--lto-Ofast
			--O2
			--icf=all
			--no-demangle
			END_LLD_OPT_ARGS
		fi
	fi

	CXXFLAGS="$(tr '\n' ' ' < "${FILE_CXXFLAGS}")"
	LDFLAGS="$(tr '\n' ' ' < "${FILE_LDFLAGS}")"
	INCFLAGS="$(tr '\n' ' ' < "${FILE_INCFLAGS}")"
	logdebug "CXXFLAGS: ${CXXFLAGS}"
	logdebug "LDFLAGS: ${LDFLAGS}"
	logdebug "INCFLAGS: ${INCFLAGS}"
}


# shellcheck disable=SC2086 # Allow compiler args to expand properly
stepped_compile(){
	set -e
    srcfile="$1"
    outfile="$2"
    PPONLY="-E -fkeep-system-includes"
    IRONLY="-emit-llvm -S"
	ASONLY="-S"
    ${CXX} ${CXXFLAGS} ${INCFLAGS} ${PPONLY} -o "${outfile}.i" "${srcfile}"
    ${CXX} ${CXXFLAGS} ${INCFLAGS} ${IRONLY} -o "${outfile}.l" "${srcfile}"
    ${CXX} ${CXXFLAGS} ${INCFLAGS} ${ASONLY} -o "${outfile}.s" "${srcfile}"
}

# shellcheck disable=SC2086 # Allow compiler args to expand properly
base_compile(){
	set -e
    srcfile="$1"
    outfile="$2"
    ${CXX} -c ${CXXFLAGS} ${INCFLAGS} "${srcfile}" -o "${outfile}.o"
	command="${CXX} -c ${CXXFLAGS} ${INCFLAGS} ${srcfile} -o ${outfile}.o"
	grep "${command}" ${FILE_RAW_COMPILE_COMMANDS} || \
		echo "${command}" >> ${FILE_RAW_COMPILE_COMMANDS}
}

compile(){
	set -e
	outfile=$(buildfile "${1}")
	mkdir -p "$(dirname "${outfile}")"
    if [ "${STEPPED_BUILD}" = "YES" ]; then
        stepped_compile "${1}" "${outfile}"
    fi
    base_compile "${1}" "${outfile}"
}

# shellcheck disable=SC2086 # Allow compiler args to expand properly
link(){
	set -e
	${LD} ${LDFLAGS} -o "${@}"
}

objfile(){
	echo "$1" | sed -e "s|${PATH_SRC}|${PATH_BLD}|" -e 's|.cpp|.o|'
}

buildfile(){
	echo "$1" | sed -e "s|${PATH_SRC}|${PATH_BLD}|" -e 's|.cpp||'
}

wayfile(){
	echo "$1" | sed -e "s|${PATH_WAYLAND_XML}|${PATH_INC}|" -e 's|.xml||'
}

generate_wayland(){
	set -e
	xmlfile="${1}"
	header="$(wayfile "${xmlfile}")-client-protocol.h"
	source="${xmlfile%.xml}-protocol.c"
	mkdir -p "$(dirname "${header}")"
	echo "header: '${header}'"
	echo "source: '${source}'"
	wayland-scanner client-header "${xmlfile}" "${header}"
	wayland-scanner public-code	  "${xmlfile}" "${source}"
}

# shellcheck disable=SC2086,SC2046 # Allow compiler args to expand properly
compile_wayland(){
	set -e
	mkdir -p "$(dirname "${1}")"
	srcfiles="$(find "${PATH_WAYLAND_XML}" -type f -name '*.c')"
	[ -e ${1} ] || ${CC} -shared $(pkg-config --libs wayland-client) $(pkg-config --cflags wayland-client) "${srcfiles}" -o "${1}"
	rm ${srcfiles}
}

cc_line(){
	read -r line
	outfile="$(echo "${line}" | sed -E 's/.*\s(\S*\.o).*/\1/' )"
	srcfile="$(echo "${line}" | sed -E 's/.*\s(\S*\.cpp).*/\1/' )"
	cat <<-ENDLINE >> "${PROJECT}/compile_commands.json"
	{
	  "directory": "${PATH_BLD}",
	  "command": "${line}",
	  "file": "${srcfile}",
	  "output": "${outfile}",
	}
	ENDLINE
}

generate_compile_commands(){
	echo "{" > "${PROJECT}/compile_commands.json"
	while read -r line; do
		echo "${line}" | cc_line
	done <"${FILE_RAW_COMPILE_COMMANDS}"
	echo "}" > "${PROJECT}/compile_commands.json"
}
