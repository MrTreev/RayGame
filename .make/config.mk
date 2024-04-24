.EXPORT_ALL_VARIABLES:

EXE_NAME	=	raygame
CXX			=	clang++
CC			=	clang
CPPSTD		=	c++23
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
CXXWARN		+=	-Werror -Wall -Wextra -Wpedantic -Wabi -Wdeprecated

ifeq (${BUILD_TYPE}, RELEASE)
	CXXFLAGS		+=	-O3
	LOG_LEVEL		=	INFO
endif
ifeq (${BUILD_TYPE}, DEBUG)
	CXXFLAGS		+=	-ggdb -Og
	LOG_LEVEL		=	DEBUG
endif

CXXFLAGS	+=	-std=${CPPSTD}
CXXFLAGS	+=	-march=${ARCH}
CXXFLAGS	+=	-mtune=${ARCH}
CXXFLAGS	+=	${INCLUDES}
CXXFLAGS	+=	-D__STDC_VERSION__=0
CXXFLAGS	+=	-DRAYGAME_LOG_${LOG_LEVEL}

ifeq (${CXX}, clang++)
	include .make/clang.mk
endif
