EXE_NAME		=	raygame
CXXSTD			=	c++23
ARCH			?=	native
BUILD_TYPE		?=	DEBUG

CXX				=	clang++
CC				=	clang

CXXFLAGS		=

RAYGAME_PREFIX	?=	${PWD}
SRC_PATH		=	${RAYGAME_PREFIX}/src
EXT_PATH		=	${RAYGAME_PREFIX}/ext
OUT_PATH		=	${RAYGAME_PREFIX}/out
BIN_PATH		=	${RAYGAME_PREFIX}/out/bin
BLD_PATH		=	${RAYGAME_PREFIX}/out/build
DOC_PATH		=	${RAYGAME_PREFIX}/out/doc
INC_PATH		=	${RAYGAME_PREFIX}/out/include
LIB_PATH		=	${RAYGAME_PREFIX}/out/lib
SYSROOT			=	${OUT_PATH}/sysroot
EXE				=	${BIN_PATH}/${EXE_NAME}

ifeq (${BUILD_TYPE}, RELEASE)
	CXXFLAGS		+=	-Ofast ${OPTFLAGS}
	LOG_LEVEL		=	INFO
endif
ifeq (${BUILD_TYPE}, DEBUG)
	CXXFLAGS		+=	-ggdb -Og
	LOG_LEVEL		=	DEBUG
endif

SRC_FILES	=	$(shell find ${SRC_PATH} -name "*.cpp")
HED_FILES	=	$(shell find ${SRC_PATH} -name "*.h")
OBJ_FILES	=	$(patsubst ${SRC_PATH}/%.cpp,${BLD_PATH}/%.o,${SRC_FILES})

LDFLAGS		=	-L${LIB_PATH}
LDFLAGS		+=	-L${SYSROOT}/lib
LDFLAGS		+=	-lc++ -lc++abi -lunwind -lraylib

CXXFLAGS	+=	-isystem${INC_PATH}
CXXFLAGS	+=	-iquote${SRC_PATH}
CXXFLAGS	+=	-std=${CXXSTD}
CXXFLAGS	+=	-DRAYGAME_LOG_${LOG_LEVEL}
CXXFLAGS	+=	-Werror
CXXFLAGS	+=	-Wall -Wextra -Wpedantic -Wdeprecated

CXXFLAGS	+=	-march=${ARCH}
CXXFLAGS	+=	-mtune=${ARCH}

ifeq (${CXX}, clang++)
	include .make/clang.mk
endif
ifeq (${CXX}, g++)
	include .make/gcc.mk
endif

include .make/raylib.mk
include .make/llvm.mk
