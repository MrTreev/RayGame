.EXPORT_ALL_VARIABLES:

EXE_NAME	=	raygame
CXX			=	clang++
#CC			=	clang
CXXSTD		=	c++23
ARCH		=	native
BUILD_TYPE	=	DEBUG
LOG_LEVEL	=	DEBUG

SRC_PATH	=	${PWD}/src
OUT_PATH	=	${PWD}/out
BIN_PATH	=	${PWD}/out/bin
BLD_PATH	=	${PWD}/out/build
DOC_PATH	=	${PWD}/out/doc
INC_PATH	=	${PWD}/out/include
LIB_PATH	=	${PWD}/out/lib
EXE			=	${BIN_PATH}/${EXE_NAME}

INCLUDES	+=	-I${INC_PATH} -I${SRC_PATH}
CXXFLAGS	+=	-Werror -Wall -Wextra -Wpedantic -Wabi -Wdeprecated
CXXFLAGS	+=	-D__STDC_VERSION__=0
CXXFLAGS	+=	-std=${CXXSTD}

CXXFLAGS	+=	-march=${ARCH}
CXXFLAGS	+=	-mtune=${ARCH}
CXXFLAGS	+=	${INCLUDES}

ifeq (${CXX}, clang++)
	include .make/clang.mk
endif

ifeq (${BUILD_TYPE}, RELEASE)
	CXXFLAGS		+=	-Ofast ${OPTFLAGS}
	LOG_LEVEL		=	INFO
endif
ifeq (${BUILD_TYPE}, DEBUG)
	CXXFLAGS		+=	-ggdb -Og
	LOG_LEVEL		=	DEBUG
endif

CXXFLAGS	+=	-DRAYGAME_LOG_${LOG_LEVEL}
