.DELETE_ON_ERROR:
include .make/config.mk

.PHONY: all
all: ${EXE}

.PHONY: clean
clean:
	cd ${RAY_PATH} && ${MAKE} clean && cd -
	rm -f compile_commands.json
	rm -rf ${OUT_PATH}

.PHONY: docs
docs: ${SRC_FILES} ${HED_FILES}
	doxygen ${PWD}/Doxyfile

.PHONY: raylib
raylib: ${LIB_PATH}/libraylib.so
${LIB_PATH}/libraylib.so:
	@mkdir -p $(dir $@)
	${MAKE} -C ${RAY_PATH} CUSTOM_CFLAGS='${RAYLIB_CFLAGS}' CUSTOM_LDFLAGS='${RAYLIB_LDFLAGS}'
	${MAKE} -C ${RAY_PATH} install
	cd ${RAY_PATH} && git clean -xf && cd -

.PHONY: libcpp-build
libcpp-build: ${LLVM_BUILD_PATH}/Makefile
${LLVM_BUILD_PATH}/Makefile:
	@mkdir -p ${LLVM_BUILD_PATH}
	cd ${LLVM_PATH} && \
		$(shell cmake ${LLVM_CMAKE_ARGS} ) && \
		cd -

.PHONY: libcpp
libcpp: ${LIB_PATH}/libc++.so
${LIB_PATH}/libc++.so: libcpp-build
	${MAKE} -C ${LLVM_BUILD_PATH} cxx cxxabi unwind
ifeq (${LLVM_DO_TESTS}, TRUE)
	${MAKE} -C ${LLVM_BUILD_PATH} test-cxx test-cxxabi test-unwind
endif
	${MAKE} -C ${LLVM_BUILD_PATH} install-cxx install-cxxabi install-unwind

${BLD_PATH}/%/%/%.o: ${SRC_PATH}/%/%/%.cpp
	@mkdir -p $(dir $@)
	${CXX} -c ${CPPFLAGS} ${CXXFLAGS} -fPIC $< -o $@

${BLD_PATH}/%/%.o: ${SRC_PATH}/%/%.cpp
	@mkdir -p $(dir $@)
	${CXX} -c ${CPPFLAGS} ${CXXFLAGS} -fPIC $< -o $@

${BLD_PATH}/%.o: ${SRC_PATH}/%.cpp
	@mkdir -p $(dir $@)
	${CXX} -c ${CPPFLAGS} ${CXXFLAGS} -fPIC $< -o $@

${EXE}: libcpp raylib ${OBJ_FILES}
	@mkdir -p $(dir $@)
	${CXX} ${CXXFLAGS} ${LDFLAGS} ${OBJ_FILES} -o $@

.PHONY: run
run:
	LD_LIBRARY_PATH=${LIB_PATH}:$$LD_LIBRARY_PATH ${EXE}

compile_commands.json: ${HED_FILES} ${SRC_FILES}
	$(shell .make/make-compile-json.sh USE_WAYLAND_DISPLAY=${USE_WAYLAND_DISPLAY})
