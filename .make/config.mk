EXE_NAME		=	raygame
CXXSTD			=	c++23
CXX				=	clang++
CC				=	clang
ARCH			?=	native
BUILD_TYPE		?=	DEBUG

export CC
export CXX

RAYGAME_PREFIX	?=	${PWD}
SRC_PATH		=	${RAYGAME_PREFIX}/src
EXT_PATH		=	${RAYGAME_PREFIX}/ext
OUT_PATH		=	${RAYGAME_PREFIX}/out
BIN_PATH		=	${RAYGAME_PREFIX}/out/bin
BLD_PATH		=	${RAYGAME_PREFIX}/out/build
DOC_PATH		=	${RAYGAME_PREFIX}/out/doc
INC_PATH		=	${RAYGAME_PREFIX}/out/include
LIB_PATH		=	${RAYGAME_PREFIX}/out/lib
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

CPPFLAGS	+=	-nostdinc++
CPPFLAGS	+=	-isystem${INC_PATH}
CPPFLAGS	+=	-isystem${INC_PATH}/c++/v1
CPPFLAGS	+=	-iquote${SRC_PATH}
CPPFLAGS	+=	-std=${CXXSTD}
CXXFLAGS	+=	-DRAYGAME_LOG_${LOG_LEVEL}
CXXFLAGS	+=	-Werror -Wall -Wextra -Wpedantic -Wabi -Wdeprecated

LDFLAGS		=	-L${LIB_PATH} -nostdlib++
LINKFLAGS	+=	-lc++ -lm -lc++abi -lunwind -lraylib
CXXFLAGS	+=	-march=${ARCH}
CXXFLAGS	+=	-mtune=${ARCH}

include .make/clang.mk
include .make/raylib.mk
include .make/llvm.mk
