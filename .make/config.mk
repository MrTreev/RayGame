.EXPORT_ALL_VARIABLES:

EXE_NAME	=	cpp-ml
CXX			=	clang++
CC			=	clang
CPPSTD		=	c++2b
ARCH		=	native
BUILD_TYPE	=	DEBUG

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
	CXXFLAGS		+=	-O2
endif
ifeq (${BUILD_TYPE}, DEBUG)
	CXXFLAGS		+=	-ggdb -Og
endif

CXXFLAGS	+=	-std=${CPPSTD}
CXXFLAGS	+=	-march=${ARCH}
CXXFLAGS	+=	-mtune=${ARCH}
CXXFLAGS	+=	${INCLUDES}

ifeq (${CXX}, clang++)
	include .make/clang.mk
endif
