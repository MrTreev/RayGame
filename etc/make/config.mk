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

CORE_PATH	=	${SRC_PATH}/core
SYST_PATH	=	${SRC_PATH}/system
WORL_PATH	=	${SRC_PATH}/world
GAME_PATH	=	${SRC_PATH}/game
TEST_PATH	=	${SRC_PATH}/test

SH_PKG_CONFIG	:=	$(shell which pkg-config)
SH_FIND			:=	$(shell which find)

CORE_SRCS	:=	$(shell ${SH_FIND} ${SRC_PATH}/core   -type f -name '*.cpp')
SYST_SRCS	:=	$(shell ${SH_FIND} ${SRC_PATH}/system -type f -name '*.cpp')
WORL_SRCS	:=	$(shell ${SH_FIND} ${SRC_PATH}/world  -type f -name '*.cpp')
GAME_SRCS	:=	$(shell ${SH_FIND} ${SRC_PATH}/game   -type f -name '*.cpp')
TEST_SRCS	:=	$(shell ${SH_FIND} ${SRC_PATH}/test   -type f -name '*.cpp')

CORE_OBJS	=	$(CORE_SRCS:${CORE_PATH}/%.cpp=${BLD_PATH}/core/%.o)
GAME_OBJS	=	$(GAME_SRCS:${GAME_PATH}/%.cpp=${BLD_PATH}/game/%.o)
SYST_OBJS	=	$(SYST_SRCS:${SYST_PATH}/%.cpp=${BLD_PATH}/system/%.o)
WORL_OBJS	=	$(WORL_SRCS:${WORL_PATH}/%.cpp=${BLD_PATH}/world/%.o)
TEST_OBJS	=	$(TEST_SRCS:${TEST_PATH}/%.cpp=${BLD_PATH}/test/%.o)

ALL_OBJS	=
ALL_OBJS	+=	${CORE_OBJS}
ALL_OBJS	+=	${GAME_OBJS}
ALL_OBJS	+=	${SYST_OBJS}
ALL_OBJS	+=	${WORL_OBJS}
ALL_OBJS	+=	${TEST_OBJS}

FULL_LIBS	=	${LIB_PATH}/libcore.so

include ${MAKEPATH}/compiler.mk
