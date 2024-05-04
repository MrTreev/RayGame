.DELETE_ON_ERROR:
include .make/config.mk
include .make/raylib.mk

.PHONY: all
all: ${EXE}

SRC_FILES		=	$(shell find ${SRC_PATH} -name "*.cpp")
HED_FILES		=	$(shell find ${SRC_PATH} -name "*.h")
OBJ_FILES		=	$(patsubst ${SRC_PATH}/%.cpp,${BLD_PATH}/%.o,${SRC_FILES})
LINK_ARGS		=	-L${LIB_PATH} -lm -lraylib

.PHONY: clean
clean:
	cd ${RAY_PATH} && ${MAKE} clean && cd -
	rm -f compile_commands.json
	rm -rf ${OUT_PATH}

.PHONY: docs
docs: ${SRC_FILES} ${HED_FILES}
	doxygen ${PWD}/Doxyfile

${LIB_PATH}/libraylib.so: ${RAYLIB_HPP_FILES}
	@mkdir -p $(dir $@)
	cd ${RAY_PATH} && ${MAKE} CUSTOM_CFLAGS='${RAYLIB_CFLAGS} ${CXXFLAGS}' CUSTOM_LDFLAGS='${RAYLIB_LDFLAGS}' && ${MAKE} install && cd -
	cd ${RAY_PATH} && git clean -xf && cd -

${RAYLIBCPP_H_INSTALL_PATH}/%.hpp: ${RAYLIBCPP_PATH}/%.hpp
	@mkdir -p $(dir $@) && cp $< $@

${BLD_PATH}/%/%/%.o: ${SRC_PATH}/%/%/%.cpp
	@mkdir -p $(dir $@)
	${CXX} -c ${CXXFLAGS} ${CPPFLAGS} -fPIC $< -o $@

${BLD_PATH}/%/%.o: ${SRC_PATH}/%/%.cpp
	@mkdir -p $(dir $@)
	${CXX} -c ${CXXFLAGS} ${CPPFLAGS} -fPIC $< -o $@

${BLD_PATH}/%.o: ${SRC_PATH}/%.cpp
	@mkdir -p $(dir $@)
	${CXX} -c ${CXXFLAGS} ${CPPFLAGS} -fPIC $< -o $@

${EXE}: ${LIB_PATH}/libraylib.so ${OBJ_FILES}
	@mkdir -p $(dir $@)
	${CXX} ${CXXFLAGS} ${CPPFLAGS} ${LINK_ARGS} ${OBJ_FILES} -o $@

.PHONY: run
run:
	LD_LIBRARY_PATH=${LIB_PATH}:$$LD_LIBRARY_PATH ${EXE}

compile_commands.json: ${HED_FILES} $(patsubst ${RAYLIBCPP_PATH}/%.hpp,${RAYLIBCPP_H_INSTALL_PATH}/%.hpp,$(wildcard ${RAYLIBCPP_PATH}/*.hpp))
	$(shell .make/make-compile-json.sh USE_WAYLAND_DISPLAY=${USE_WAYLAND_DISPLAY})
