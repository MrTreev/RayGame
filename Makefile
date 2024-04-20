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
	rm -rf ${OUT_PATH}

.PHONY: docs
docs:
	doxygen ${PWD}/Doxyfile

.PHONY: raylib
raylib: ${LIB_PATH}/libraylib.so

${LIB_PATH}/libraylib.so:
	mkdir -p $(dir $@)
	cd ${RAY_PATH} && ${MAKE} && ${MAKE} install
	cd ${RAY_PATH} && git clean -xf # Clean up after build

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
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:${BLD_PATH} ${EXE}
