EXE_NAME	=	raygame
COMPILER	?=	clang
ARCH		?=	native
CXXSTD		=	c++2c
CXXLIB		=	libstdc++
RTLIB		=	compiler-rt
CPU			=

BUILD_TYPE	?=	DEBUG
BUILD_ASAN	?=	FALSE
BUILD_MSAN	?=	FALSE
BUILD_UBSAN	?=	FALSE

PKG_CONFIG	=	pkg-config

PROJECT		=	${PWD}
SRC_PATH	=	${PROJECT}/src
EXT_PATH	=	${PROJECT}/ext
OUT_PATH	=	${PROJECT}/out
BIN_PATH	=	${PROJECT}/out/bin
BLD_PATH	=	${PROJECT}/out/build
DOC_PATH	=	${PROJECT}/out/doc
INC_PATH	=	${PROJECT}/out/include
LIB_PATH	=	${PROJECT}/out/lib
MAKEFILES	=	${PROJECT}/make

EXE			=	${BIN_PATH}/${EXE_NAME}

${OUT_PATH}:
	mkdir -p ${OUT_PATH}

${BIN_PATH}: ${OUT_PATH}
	mkdir -p ${BIN_PATH}

${BLD_PATH}: ${OUT_PATH}
	mkdir -p ${BLD_PATH}

${DOC_PATH}: ${OUT_PATH}
	mkdir -p ${DOC_PATH}

${INC_PATH}: ${OUT_PATH}
	mkdir -p ${INC_PATH}

${LIB_PATH}: ${OUT_PATH}
	mkdir -p ${LIB_PATH}

include ${MAKEFILES}/compiler.mk
