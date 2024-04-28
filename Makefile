.DELETE_ON_ERROR:
include .make/config.mk
include .make/raylib.mk

.PHONY: all
all: ${EXE}

SRC_FILES		=	$(shell find ${SRC_PATH} -name "*.cpp")
OBJ_FILES		=	$(patsubst ${SRC_PATH}/%.cpp,${BLD_PATH}/%.o,${SRC_FILES})
LINK_ARGS		=	-L${LIB_PATH} -lm -lraylib

.PHONY: clean
clean:
	cd ${RAY_PATH} && ${MAKE} clean && cd -
	rm -f compile_commands.json
	rm -rf ${OUT_PATH}

.PHONY: docs
docs:
	doxygen ${PWD}/Doxyfile

.PHONY: raylib
raylib: ${LIB_PATH}/libraylib.so ${RAYLIBCPP_H_INSTALL_PATH}/raylib-cpp.hpp

${LIB_PATH}/libraylib.so:
	mkdir -p $(dir $@)
	cd ${RAY_PATH} && ${MAKE} && ${MAKE} install && cd -
	cd ${RAY_PATH} && git clean -xf && cd - # Clean up after build
	$(shell find ${RAY_PATH} -type f -name '*.h' -exec cp -f {} ${RAYLIB_H_INSTALL_PATH} \;)

${RAYLIBCPP_H_INSTALL_PATH}/raylib-cpp.hpp: $(wildcard ${RAYLIBCPP_PATH}/*.hpp) ${LIB_PATH}/libraylib.so
	mkdir -p ${RAYLIBCPP_H_INSTALL_PATH}
	$(shell find ${RAYLIBCPP_PATH} -type f -name '*.hpp' -exec cp -f --target-directory=${RAYLIBCPP_H_INSTALL_PATH} {} \;)

${BLD_PATH}/%/%/%.o: ${SRC_PATH}/%/%/%.cpp
	mkdir -p $(dir $@)
	${CXX} -c ${CPPFLAGS} -fPIC ${CXXFLAGS} $< -o $@

${BLD_PATH}/%/%.o: ${SRC_PATH}/%/%.cpp
	mkdir -p $(dir $@)
	${CXX} -c ${CPPFLAGS} -fPIC ${CXXFLAGS} $< -o $@

${BLD_PATH}/%.o: ${SRC_PATH}/%.cpp
	mkdir -p $(dir $@)
	${CXX} -c ${CPPFLAGS} -fPIC ${CXXFLAGS} $< -o $@

${EXE}: raylib ${OBJ_FILES}
	mkdir -p $(dir $@)
	${CXX} ${CPPFLAGS} ${CXXFLAGS} ${LINK_ARGS} ${OBJ_FILES} -o $@

.PHONY: run
run:
	LD_LIBRARY_PATH=${LIB_PATH}:$$LD_LIBRARY_PATH ${EXE}

compile_commands.json: ${SRC_FILES}
	$(shell .make/make-compile-json.sh USE_WAYLAND_DISPLAY=${USE_WAYLAND_DISPLAY})
