PROJECT					=	${PWD}
CXX						=	clang++
CC						=	clang
BUILD_TYPE				=	DEBUG
BUILD_ASAN				=	FALSE
BUILD_MSAN				=	FALSE
BUILD_UBSAN				=	FALSE
ETC						=	${PROJECT}/etc
CMAKE_ARGS				=	-G Ninja -S src -B build --log-level=DEBUG -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=${CXX}
PKG_CONFIG				=	pkg-config
WAYLAND_FLAGS 			=	$(shell $(PKG_CONFIG) wayland-client --cflags --libs)
WAYLAND_PROTOCOL_DIR	=	${ETC}/wayland-protocols
WAYLAND_PROCESSED_DIR	=	${ETC}/wayland-sources
WAYLAND_PROTOCOLS		=	$(wildcard ${WAYLAND_PROTOCOL_DIR}/*.xml)
WAYLAND_SOURCES			=	$(WAYLAND_PROTOCOLS:${WAYLAND_PROTOCOL_DIR}%.xml=${WAYLAND_PROCESSED_DIR}%-protocol.c)
WAYLAND_CLIENT_HEADERS	=	$(WAYLAND_PROTOCOLS:${WAYLAND_PROTOCOL_DIR}%.xml=${WAYLAND_PROCESSED_DIR}%-client-protocol.h)

LIB_NAME				=	raygame_wayland
LIB_SUFFIX				=	.so
BUILD_LIB				=	${WAYLAND_PROCESSED_DIR}/lib${LIB_NAME}${LIB_SUFFIX}
CFLAGS					+=	-shared -fPIC

ifeq (${BUILD_TYPE}, DEBUG)
CFLAGS	+=	-Og -ggdb -fno-omit-frame-pointer
else
CFLAGS	+=	-Ofast
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

.PHONY: all
all: cmake

.PHONY: clean
clean:
	rm -rf ${WAYLAND_PROCESSED_DIR} ${PROJECT}/build

${WAYLAND_PROCESSED_DIR}%-protocol.c: ${WAYLAND_PROTOCOL_DIR}%.xml
	@mkdir -p ${WAYLAND_PROCESSED_DIR}
	wayland-scanner public-code $< $@
	@echo ""

${WAYLAND_PROCESSED_DIR}%-client-protocol.h: ${WAYLAND_PROTOCOL_DIR}%.xml
	@mkdir -p ${WAYLAND_PROCESSED_DIR}
	wayland-scanner client-header $< $@
	@sed -i 's/"wayland-client.h"/<wayland-client.h>/' $@
	@echo ""

${BUILD_LIB}: ${WAYLAND_SOURCES}
	${CC} -shared ${LDFLAGS} $^ -o $@
	@echo ""

.PHONY: cmake
cmake: ${WAYLAND_CLIENT_HEADERS} ${BUILD_LIB}
	@echo ""
	cmake ${CMAKE_ARGS}
	@echo ""
	cmake --build build
