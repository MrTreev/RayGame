.EXPORT_ALL_VARIABLES:

CXXFLAGS	+=	-isystem${INC_PATH}
CXXFLAGS	+=	-iquote${SRC_PATH}

ifdef CXXSTD
CXXFLAGS	+=	-std=${CXXSTD}
endif
ifdef CXXLIB
CXXFLAGS	+=	-stdlib=${CXXLIB}
endif
ifdef RTLIB
#CXXFLAGS	+=	-rtlib=${RTLIB}
endif
ifdef ARCH
CXXFLAGS	+=	-march=${ARCH}
CXXFLAGS	+=	-mtune=${ARCH}
endif

CXXFLAGS	+=	-Qunused-arguments
LDFLAGS		+=	-Qunused-arguments
LDFLAGS		+=	-lc++ -lc++abi -lunwind

ifeq (${COMPILER}, gcc)
	CXX		=	g++
	CC		=	gcc
	include ${MAKEPATH}/compilers/gcc.mk
endif
ifeq (${COMPILER}, clang)
	CXX		=	clang++
	CC		=	clang
	include ${MAKEPATH}/compilers/clang.mk
endif

ifeq (${BUILD_TYPE}, DEBUG)
	CFLAGS		+=	-ggdb -Og -fno-omit-frame-pointer
	CXXFLAGS	+=	-ggdb -Og -fno-omit-frame-pointer
	LOG_LEVEL	=	DEBUG
else
	CFLAGS		+=	-Ofast
	CXXFLAGS	+=	-Ofast ${OPTFLAGS}
	LOG_LEVEL	=	INFO
endif

CXXFLAGS	+=	-DRAYGAME_LOG_${LOG_LEVEL}
CXXFLAGS	+=	-DRAYGAME_GUI_${GUI_TYPE}

ifeq (${BUILD_ASAN}, TRUE)
	CFLAGS		+=	-fsanitize=address
	CXXFLAGS	+=	-fsanitize=address
endif
ifeq (${BUILD_MSAN}, TRUE)
	CFLAGS		+=	-fsanitize=memory
	CXXFLAGS	+=	-fsanitize=memory
endif
ifeq (${BUILD_UBSAN}, TRUE)
	CFLAGS		+=	-fsanitize=undefined
	CXXFLAGS	+=	-fsanitize=undefined
endif
