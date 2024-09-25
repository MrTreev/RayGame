include etc/make/config.mk

################################################################################
### TARGETS                                                                  ###
################################################################################
.PHONY: all
all: ${EXE} test

.PHONY: run
run: ${EXE}
	@${EXE}

.PHONY: test
test: ${TEST_RUNNER}
	@${TEST_RUNNER}

.PHONY: clean
clean:
	@rm -rf ${OUT_PATH}

################################################################################
### WAYLAND                                                                  ###
################################################################################
include etc/make/wayland.mk
WAYLAND_LIB=${LIB_PATH}/libraygame_wayland.so

${WAYLAND_PROCESSED_DIR}/%-client-protocol.c: ${WAYLAND_PROTOCOL_DIR}/%.xml
	@mkdir -p $(dir $@)
	wayland-scanner public-code $< $@

${INC_PATH}/%-client-protocol.h: ${WAYLAND_PROTOCOL_DIR}/%.xml
	@mkdir -p $(dir $@)
	wayland-scanner client-header $< $@
	@sed -i 's/"wayland-client.h"/<wayland-client.h>/' $@

${WAYLAND_LIB}: ${WAYLAND_SRCS} | ${WAYLAND_HDRS}
	@mkdir -p $(dir $@)
	${CC} ${LIBFLAGS} ${WAYLAND_LDFLAGS} ${LDFLAGS} $^ -o $@

################################################################################
### RULES                                                                    ###
################################################################################
WAYPATH=core/windowimpl/wayland

${BLD_PATH}/${WAYPATH}/%.o: ${SRC_PATH}/${WAYPATH}/%.cpp | ${WAYLAND_LIB}
	@mkdir -p $(shell dirname $@)
	${CXX} -c -fPIC ${CXXFLAGS} ${WARNS} $< -o $@

${BLD_PATH}/%.o: ${SRC_PATH}/%.cpp
	@mkdir -p $(shell dirname $@)
	${CXX} -c -fPIC ${CXXFLAGS} ${WARNS} $< -o $@


################################################################################
### LIBS                                                                     ###
################################################################################
${LIB_PATH}/libcore.so: ${CORE_OBJS} ${WAYLAND_LIB}
	@mkdir -p $(shell dirname $@)
	${CXX} ${LIBFLAGS} ${LDFLAGS} ${CORE_LDFLAGS} ${WARNS} $^ -o $@

${LIB_PATH}/libsystem.so: ${SYST_OBJS}
	@mkdir -p $(shell dirname $@)
	${CXX} ${LIBFLAGS} ${LDFLAGS} ${SYSTEM_LDFLAGS} ${WARNS} $^ -o $@

${LIB_PATH}/libworld.so: ${WORL_OBJS}
	@mkdir -p $(shell dirname $@)
	${CXX} ${LIBFLAGS} ${LDFLAGS} ${WORLD_LDFLAGS} ${WARNS} $^ -o $@

################################################################################
### GAME                                                                     ###
################################################################################
${EXE}: ${GAME_OBJS} ${FULL_LIBS}
	@mkdir -p $(shell dirname $@)
	${CXX} ${LDFLAGS} ${GAME_LDFLAGS} ${WARNS} $^ -o $@

################################################################################
### TEST                                                                     ###
################################################################################
TEST_CXXFLAGS	+=	-isystem${ETC_PATH}/doctest

${BLD_PATH}/test/%.o: ${SRC_PATH}/test/%.cpp
	@mkdir -p $(shell dirname $@)
	${CXX} -c -fPIC ${CXXFLAGS} ${WARNS} ${TEST_CXXFLAGS} $< -o $@

${TEST_RUNNER}: ${TEST_OBJS} ${FULL_LIBS}
	@mkdir -p $(shell dirname $@)
	${CXX} ${TEST_LDFLAGS} ${LDFLAGS} ${WARNS} $^ -o $@

${TEST_OBJS}: ${TEST_SRCS}

-include $(ALL_OBJS:.o=.d)
