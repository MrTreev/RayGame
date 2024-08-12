CORE_PATH	=	${SRC_PATH}/core
SYSTEM_PATH	=	${SRC_PATH}/system
WORLD_PATH	=	${SRC_PATH}/world
GAME_PATH	=	${SRC_PATH}/game
CORE_HDRS	=	$(shell find ${CORE_PATH} -type f -name '*.h')
CORE_SRCS	=	$(shell find ${CORE_PATH} -type f -name '*.cpp')
CORE_OBJS	=	$(CORE_SRCS:${SRC_PATH}/%.cpp=${BUILD_PATH}.o)
SYSTEM_HDRS	=	$(shell find ${SYSTEM_PATH} -type f -name '*.h')
SYSTEM_SRCS	=	$(shell find ${SYSTEM_PATH} -type f -name '*.cpp')
SYSTEM_OBJS	=	$(SYSTEM_SRCS:${SRC_PATH}/%.cpp=${BUILD_PATH}.o)
WORLD_HDRS	=	$(shell find ${WORLD_PATH} -type f -name '*.h')
WORLD_SRCS	=	$(shell find ${WORLD_PATH} -type f -name '*.cpp')
WORLD_OBJS	=	$(WORLD_SRCS:${SRC_PATH}/%.cpp=${BUILD_PATH}.o)
GAME_HDRS	=	$(shell find ${GAME_PATH} -type f -name '*.h')
GAME_SRCS	=	$(shell find ${GAME_PATH} -type f -name '*.cpp')
GAME_OBJS	=	$(GAME_SRCS:${SRC_PATH}/%.cpp=${BUILD_PATH}.o)

${BUILD_PATH}%.ii: ${SRC_PATH}%.cpp
	@mkdir -p $(dir $@)
	${CXX} -fsyntax-only ${CPPFLAGS} ${WARNS} $< -o $@

%.s: %.ii
	@mkdir -p $(dir $@)
	${CXX} -S ${CXXFLAGS} ${WARNS} $< -o $@

%.o: %.s
	@mkdir -p $(dir $@)
	${CXX} -c ${ASSFLAGS} ${WARNS} $< -o $@

${LIB_PATH}/libcore.so: ${CORE_OBJS}
	@mkdir -p $(dir $@)
	${CXX} -shared ${LDFLAGS} ${CORE_LDFLAGS} ${WARNS} $^ -o $@

${LIB_PATH}/libsystem.so: ${SYSTEM_OBJS}
	@mkdir -p $(dir $@)
	${CXX} -shared ${LDFLAGS} ${SYSTEM_LDFLAGS} ${WARNS} $^ -o $@

${LIB_PATH}/libworld.so: ${WORLD_OBJS}
	@mkdir -p $(dir $@)
	${CXX} -shared ${LDFLAGS} ${WORLD_LDFLAGS} ${WARNS} $^ -o $@

${EXE}: ${LIB_PATH}/libcore.so ${LIB_PATH}/libsystem.so ${LIB_PATH}/libworld.so ${GAME_OBJS}
	@mkdir -p $(dir $@)
	${CXX} -shared ${LDFLAGS} ${GAME_LDFLAGS} ${WARNS} $^ -o $@
