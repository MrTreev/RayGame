.DELETE_ON_ERROR:
include .make/config.mk

.PHONY: all
all: ${EXE}

.PHONY: clean
clean:
	cd ${RAY_PATH} && ${MAKE} clean && cd -
	rm -rf ${OUT_PATH}

.PHONY: docs
docs: ${SRC_FILES} ${HED_FILES}
	doxygen ${PWD}/Doxyfile

.PHONY: raylib
raylib: ${LIB_PATH}/libraylib.so
${LIB_PATH}/libraylib.so:
	@mkdir -p $(dir $@)
	make -C ${RAY_PATH} CUSTOM_CFLAGS='${RAYLIB_CFLAGS}' CUSTOM_LDFLAGS='${RAYLIB_LDFLAGS}'
	make -C ${RAY_PATH} install
	cd ${RAY_PATH} && git clean -xf && cd -

${BLD_PATH}/%/%/%.o: ${SRC_PATH}/%/%/%.h
${BLD_PATH}/%/%.o: ${SRC_PATH}/%/%.h
${BLD_PATH}/%.o: ${SRC_PATH}/%.h

${BLD_PATH}/%/%/%.o: ${SRC_PATH}/%/%/%.cpp
	@mkdir -p $(dir $@)
	${CXX} -c ${CXXFLAGS} -fPIC $< -o $@

${BLD_PATH}/%/%.o: ${SRC_PATH}/%/%.cpp
	@mkdir -p $(dir $@)
	${CXX} -c ${CXXFLAGS} -fPIC $< -o $@

${BLD_PATH}/%.o: ${SRC_PATH}/%.cpp
	@mkdir -p $(dir $@)
	${CXX} -c ${CXXFLAGS} -fPIC $< -o $@

${EXE}: raylib ${OBJ_FILES}
	@mkdir -p $(dir $@)
	${CXX} ${CXXFLAGS} ${LDFLAGS} ${OBJ_FILES} -o $@

.PHONY: run
run:
	LD_LIBRARY_PATH=${LIB_PATH}:$$LD_LIBRARY_PATH ${EXE}

compile_commands.json: ${HED_FILES} ${SRC_FILES}
	${RAYGAME_PREFIX}/.make/make-compile-json.sh
