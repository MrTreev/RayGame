CFLAGS		=

CXXFLAGS	+=	-isystem${INC_PATH}
CXXFLAGS	+=	-iquote${SRC_PATH}

ifdef CXXSTD
CXXFLAGS	+=	-std=${CXXSTD}
endif
ifdef CXXLIB
CXXFLAGS	+=	-stdlib=${CXXLIB}
endif
ifdef RTLIB
CXXFLAGS	+=	-rtlib=${RTLIB}
endif
ifdef ARCH
CXXFLAGS	+=	-march=${ARCH}
CXXFLAGS	+=	-mtune=${ARCH}
endif

CXXFLAGS	+=	-DRAYGAME_LOG_${LOG_LEVEL}
WARNS		+=	-Werror
WARNS		+=	-Wall -Wextra -Wpedantic -Wdeprecated
LDFLAGS		+=	-lc++ -lc++abi -lunwind

ifeq (${COMPILER}, "gcc")
	CXX		?=	g++
	CC		?=	gcc
	include ${MAKEFILES}/compilers/gcc.mk
endif
ifeq (${COMPILER}, "clang")
	CXX		?=	clang++
	CC		?=	clang
	include ${MAKEFILES}/compilers/clang.mk
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
