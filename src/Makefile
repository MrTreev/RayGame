CORE_PATH	=	${SRC_PATH}/core
SYSTEM_PATH	=	${SRC_PATH}/system
WORLD_PATH	=	${SRC_PATH}/world
GAME_PATH	=	${SRC_PATH}/game
CORE_HDRS	=	$(shell find ${CORE_PATH} -type f -name '*.h')
CORE_SRCS	=	$(shell find ${CORE_PATH} -type f -name '*.cpp')
CORE_OBJS	=	$(CORE_SRCS:${SRC_PATH}/%.cpp=${BLD_PATH}/%.o)
SYSTEM_HDRS	=	$(shell find ${SYSTEM_PATH} -type f -name '*.h')
SYSTEM_SRCS	=	$(shell find ${SYSTEM_PATH} -type f -name '*.cpp')
SYSTEM_OBJS	=	$(SYSTEM_SRCS:${SRC_PATH}/%.cpp=${BLD_PATH}/%.o)
WORLD_HDRS	=	$(shell find ${WORLD_PATH} -type f -name '*.h')
WORLD_SRCS	=	$(shell find ${WORLD_PATH} -type f -name '*.cpp')
WORLD_OBJS	=	$(WORLD_SRCS:${SRC_PATH}/%.cpp=${BLD_PATH}/%.o)
GAME_HDRS	=	$(shell find ${GAME_PATH} -type f -name '*.h')
GAME_SRCS	=	$(shell find ${GAME_PATH} -type f -name '*.cpp')
GAME_OBJS	=	$(GAME_SRCS:${SRC_PATH}/%.cpp=${BLD_PATH}/%.o)
FULL_LIBS	=	${LIB_PATH}/libcore.so ${LIB_PATH}/libraygame_wayland.so

.PHONY: all
all: ${EXE}

${BLD_PATH}/%.o: ${SRC_PATH}/%.cpp
	@mkdir -p $(shell dirname $@)
	@${CXX} -c -fPIC ${CXXFLAGS} ${WARNS} $< -o $@

${LIB_PATH}/libcore.so: ${CORE_OBJS}
	@mkdir -p $(shell dirname $@)
	@${CXX} -shared -fPIC ${LDFLAGS} ${CORE_LDFLAGS} ${WARNS} $^ -o $@

${LIB_PATH}/libsystem.so: ${SYSTEM_OBJS}
	@mkdir -p $(shell dirname $@)
	@${CXX} -shared -fPIC ${LDFLAGS} ${SYSTEM_LDFLAGS} ${WARNS} $^ -o $@

${LIB_PATH}/libworld.so: ${WORLD_OBJS}
	@mkdir -p $(shell dirname $@)
	@${CXX} -shared -fPIC ${LDFLAGS} ${WORLD_LDFLAGS} ${WARNS} $^ -o $@

${EXE}: ${GAME_OBJS} ${FULL_LIBS}
	@mkdir -p $(shell dirname $@)
	@${CXX} ${LDFLAGS} ${GAME_LDFLAGS} ${WARNS} $^ -o $@

################################################################################
### TEST                                                                     ###
################################################################################
TEST_PATH		=	${SRC_PATH}/test
TEST_HDR		=	${ETC}/tts/standalone/tts/tts.hpp
TEST_SRCS		=	$(shell find ${TEST_PATH} -type f -name '*.cpp')
TEST_OBJS		=	$(TEST_SRCS:${SRC_PATH}/%.cpp=${BLD_PATH}/%.o)
TEST_CXXFLAGS	+=	-isystem${ETC_PATH}/tts/standalone
TEST_CXXFLAGS	+=	-Wno-global-constructors
TEST_CXXFLAGS	+=	-Wno-c99-designator
TEST_CXXFLAGS	+=	-Wno-c99-extensions
TEST_CXXFLAGS	+=	-Wno-c99-compat

${BLD_PATH}/test/%.o: ${SRC_PATH}/test/%.cpp
	@${CXX} -c -fPIC ${CXXFLAGS} ${WARNS} ${TEST_CXXFLAGS} $< -o $@
${TEST_RUNNER}: ${TEST_OBJS} ${FULL_LIBS}
	@${CXX} ${TEST_LDFLAGS} ${LDFLAGS} ${WARNS} $^ -o $@
${TEST_OBJS}: ${TEST_SRCS}
.PHONY: test
test: ${TEST_RUNNER}
