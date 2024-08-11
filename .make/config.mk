EXE_NAME	=	raygame

COMPILER	?=	clang
ARCH		?=	native

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
MAKEFILES	=	${PROJECT}/.make

EXE			=	${BIN_PATH}/${EXE_NAME}

include ${MAKEFILES}/compiler.mk
