WAYLAND_PROTOCOL_DIR	=	${ETC_PATH}/wayland-protocols
WAYLAND_PROCESSED_DIR	=	${ETC_PATH}/wayland-sources

WAYLAND_CFLAGS 			=	$(shell $(PKG_CONFIG) wayland-client --cflags)
WAYLAND_LDFLAGS			=	$(shell $(PKG_CONFIG) wayland-client --libs)
WAYLAND_PROTOCOLS		=	$(wildcard ${WAYLAND_PROTOCOL_DIR}/*.xml)

WAYLAND_SRCS			=	$(WAYLAND_PROTOCOLS:${WAYLAND_PROTOCOL_DIR}/%.xml=${WAYLAND_PROCESSED_DIR}/%-protocol.c)
WAYLAND_HDRS			=	$(WAYLAND_PROTOCOLS:${WAYLAND_PROTOCOL_DIR}/%.xml=${WAYLAND_PROCESSED_DIR}/%-protocol.h)
WAYLAND_INCS			=	$(WAYLAND_PROTOCOLS:${WAYLAND_PROTOCOL_DIR}/%.xml=${INC_PATH}/%-protocol.h)
export WAYLAND_INCS

all: ${WAYLAND_INCS} ${LIB_PATH}/libraygame_wayland.so

${WAYLAND_PROCESSED_DIR}/%-protocol.c: ${WAYLAND_PROTOCOL_DIR}/%.xml
	@mkdir -p $(dir $@)
	wayland-scanner public-code $< $@

${WAYLAND_PROCESSED_DIR}/%-protocol.h: ${WAYLAND_PROTOCOL_DIR}/%.xml
	@mkdir -p $(dir $@)
	wayland-scanner client-header $< $@
	@sed -i 's/"wayland-client.h"/<wayland-client.h>/' $@

${LIB_PATH}/libraygame_wayland.so: ${WAYLAND_SRCS} ${WAYLAND_HDRS}
	@mkdir -p $(dir $@)
	${CC} -shared -fPIC ${WAYLAND_LDFLAGS} ${LDFLAGS} ${WAYLAND_SRCS} -o $@

${INC_PATH}/%.h: ${WAYLAND_PROCESSED_DIR}/%.h
	@mkdir -p $(dir $@)
	cp $< $@
