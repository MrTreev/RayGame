CXXSTD		=	c++2c

CXXFLAGS	=	-lc++ -lc++abi -lunwind
CFLAGS		=
CXXFLAGS	+=	-isystem${INC_PATH}
CXXFLAGS	+=	-iquote${SRC_PATH}
CXXFLAGS	+=	-std=${CXXSTD}
CXXFLAGS	+=	-DRAYGAME_LOG_${LOG_LEVEL}
CXXFLAGS	+=	-Werror
CXXFLAGS	+=	-Wall -Wextra -Wpedantic -Wdeprecated

CXXFLAGS	+=	-march=${ARCH}
CXXFLAGS	+=	-mtune=${ARCH}

ifeq(${COMPILER}, "gcc")
	CXX		?=	g++
	CC		?=	gcc
	include ${MAKEFILES}/gcc.mk
endif
ifeq(${COMPILER}, "clang")
	CXX		?=	clang++
	CC		?=	clang
	include ${MAKEFILES}/clang.mk
endif

ifeq (${BUILD_TYPE}, DEBUG)
	CFLAGS		+=	-Og -ggdb -fno-omit-frame-pointer
	CXXFLAGS	+=	-ggdb -Og
	LOG_LEVEL	=	DEBUG
else
	CFLAGS		+=	-Ofast
	CXXFLAGS	+=	-Ofast ${OPTFLAGS}
	LOG_LEVEL	=	INFO
endif

ifeq (${BUILD_ASAN}, TRUE)
	CFLAGS	+=	-fsanitize=address
endif
ifeq (${BUILD_MSAN}, TRUE)
	CFLAGS	+=	-fsanitize=memory
endif
ifeq (${BUILD_UBSAN}, TRUE)
	CFLAGS	+=	-fsanitize=undefined
endif
