.EXPORT_ALL_VARIABLES:
EXE_NAME	=	RayGame
COMPILER	=	clang
ARCH		=	native
CXXSTD		=	c++2c
CXXLIB		=	libstdc++
RTLIB		=	compiler-rt
CPU			=

BUILD_TYPE	=	DEBUG
BUILD_ASAN	=	FALSE
BUILD_MSAN	=	FALSE
BUILD_UBSAN	=	FALSE
GUI_TYPE	=	WAYLAND

PKG_CONFIG	=	pkg-config

PROJECT		=	${PWD}
SRC_PATH	=	${PROJECT}/src
ETC_PATH	=	${PROJECT}/etc
EXT_PATH	=	${PROJECT}/ext
OUT_PATH	=	${PROJECT}/out
BIN_PATH	=	${PROJECT}/out/bin
BLD_PATH	=	${PROJECT}/out/build
DOC_PATH	=	${PROJECT}/out/doc
INC_PATH	=	${PROJECT}/out/include
LIB_PATH	=	${PROJECT}/out/lib
MAKEPATH	=	${ETC_PATH}/make
EXE			=	${BIN_PATH}/${EXE_NAME}
TEST_RUNNER	=	${BIN_PATH}/TestRunner

include ${MAKEPATH}/compiler.mk
