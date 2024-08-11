WAYLAND_FLAGS 			=	$(shell $(PKG_CONFIG) wayland-client --cflags --libs)
WAYLAND_PROTOCOL_DIR	=	${ETC_PATH}/wayland-protocols
WAYLAND_PROCESSED_DIR	=	${ETC_PATH}/wayland-sources
WAYLAND_PROTOCOLS		=	$(wildcard ${WAYLAND_PROTOCOL_DIR}/*.xml)
WAYLAND_SOURCES			=	$(WAYLAND_PROTOCOLS:${WAYLAND_PROTOCOL_DIR}%.xml=${WAYLAND_PROCESSED_DIR}%-protocol.c)
WAYLAND_CLIENT_HEADERS	=	$(WAYLAND_PROTOCOLS:${WAYLAND_PROTOCOL_DIR}%.xml=${WAYLAND_PROCESSED_DIR}%-client-protocol.h)

${WAYLAND_PROCESSED_DIR}%-protocol.c: ${WAYLAND_PROTOCOL_DIR}%.xml
	@mkdir -p ${WAYLAND_PROCESSED_DIR}
	wayland-scanner public-code $< $@
	@echo ""

${WAYLAND_PROCESSED_DIR}%-client-protocol.h: ${WAYLAND_PROTOCOL_DIR}%.xml
	@mkdir -p ${WAYLAND_PROCESSED_DIR}
	wayland-scanner client-header $< $@
	@sed -i 's/"wayland-client.h"/<wayland-client.h>/' $@
	@echo ""

${WAYLAND_PROCESSED_DIR}/libraygame_wayland.so: ${WAYLAND_SOURCES}
	${CC} -shared ${LDFLAGS} $^ -o $@
	@echo ""
