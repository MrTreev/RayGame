include etc/make/config.mk

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
${WAYLAND_PROCESSED_DIR}/%${WAYLAND_SUFFIX}.c: ${WAYLAND_PROTOCOL_DIR}/%.xml
	@mkdir -p $(dir $@)
	@wayland-scanner public-code $< $@

${WAYLAND_PROCESSED_DIR}/%${WAYLAND_SUFFIX}.h: ${WAYLAND_PROTOCOL_DIR}/%.xml
	@mkdir -p $(dir $@)
	@wayland-scanner client-header $< $@
	@sed -i 's/"wayland-client.h"/<wayland-client.h>/' $@

${LIB_PATH}/libraygame_wayland.so: ${WAYLAND_SRCS} ${WAYLAND_HDRS}
	@mkdir -p $(dir $@)
	@${CC} -shared -fPIC ${WAYLAND_LDFLAGS} ${LDFLAGS} ${WAYLAND_SRCS} -o $@

${INC_PATH}/%.h: ${WAYLAND_PROCESSED_DIR}/%.h
	@mkdir -p $(dir $@)
	@cp $< $@

################################################################################
### RULES                                                                    ###
################################################################################
${BLD_PATH}/%.o: ${SRC_PATH}/%.cpp
	@mkdir -p $(shell dirname $@)
	@${CXX} -c -fPIC ${CXXFLAGS} ${WARNS} $< -o $@
WAYPATH=core/windowimpl/wayland
${BLD_PATH}/${WAYPATH}/%.o: ${SRC_PATH}/${WAYPATH}/%.cpp ${WAYLAND_INCS}
	@mkdir -p $(shell dirname $@)
	@${CXX} -c -fPIC ${CXXFLAGS} ${WARNS} $< -o $@


################################################################################
### LIBS                                                                     ###
################################################################################
${LIB_PATH}/libcore.so: ${CORE_OBJS} ${LIB_PATH}/libraygame_wayland.so
	@mkdir -p $(shell dirname $@)
	@${CXX} -shared -fPIC ${LDFLAGS} ${CORE_LDFLAGS} ${WARNS} $^ -o $@

${LIB_PATH}/libsystem.so: ${SYST_OBJS}
	@mkdir -p $(shell dirname $@)
	@${CXX} -shared -fPIC ${LDFLAGS} ${SYSTEM_LDFLAGS} ${WARNS} $^ -o $@

${LIB_PATH}/libworld.so: ${WORL_OBJS}
	@mkdir -p $(shell dirname $@)
	@${CXX} -shared -fPIC ${LDFLAGS} ${WORLD_LDFLAGS} ${WARNS} $^ -o $@

################################################################################
### GAME                                                                     ###
################################################################################
${EXE}: $(GAME_SRCS:${SRC_PATH}/%.cpp=${BLD_PATH}/%.o) ${FULL_LIBS}
	@mkdir -p $(shell dirname $@)
	@${CXX} ${LDFLAGS} ${GAME_LDFLAGS} ${WARNS} $^ -o $@

################################################################################
### TEST                                                                     ###
################################################################################
TEST_CXXFLAGS	+=	-isystem${ETC_PATH}/doctest
${BLD_PATH}/test/%.o: ${SRC_PATH}/test/%.cpp
	@mkdir -p $(shell dirname $@)
	@${CXX} -c -fPIC ${CXXFLAGS} ${WARNS} ${TEST_CXXFLAGS} $< -o $@
${TEST_RUNNER}: ${TEST_OBJS} ${FULL_LIBS}
	@mkdir -p $(shell dirname $@)
	@${CXX} ${TEST_LDFLAGS} ${LDFLAGS} ${WARNS} $^ -o $@
${TEST_OBJS}: ${TEST_SRCS}

-include $(ALL_OBJS:.o=.d)
