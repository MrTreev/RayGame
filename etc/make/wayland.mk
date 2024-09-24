.EXPORT_ALL_VARIABLES:

WAYLAND_SUFFIX			:=	-client-protocol
WAYLAND_PROTOCOL_DIR	:=	${ETC_PATH}/wayland-protocols
WAYLAND_PROCESSED_DIR	:=	${ETC_PATH}/wayland-sources
WAYLAND_CFLAGS 			:=	$(shell $(SH_PKG_CONFIG) wayland-client --cflags)
WAYLAND_LDFLAGS			:=	$(shell $(SH_PKG_CONFIG) wayland-client --libs)
WAYLAND_PROTOCOLS		:=	$(wildcard ${WAYLAND_PROTOCOL_DIR}/*.xml)

WAYLAND_SRCS			:=	$(WAYLAND_PROTOCOLS:${WAYLAND_PROTOCOL_DIR}/%.xml=${WAYLAND_PROCESSED_DIR}/%${WAYLAND_SUFFIX}.c)
WAYLAND_HDRS			:=	$(WAYLAND_PROTOCOLS:${WAYLAND_PROTOCOL_DIR}/%.xml=${WAYLAND_PROCESSED_DIR}/%${WAYLAND_SUFFIX}.h)
WAYLAND_HDRS			:=	$(WAYLAND_PROTOCOLS:${WAYLAND_PROTOCOL_DIR}/%.xml=${INC_PATH}/%${WAYLAND_SUFFIX}.h)
