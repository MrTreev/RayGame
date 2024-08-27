COMPILER=clang
export COMPILER

include etc/make/config.mk

.PHONY: all
all: build test

.PHONY: build
build: ${EXE}
${EXE}:
	@mkdir -p ${OUT_PATH} ${BIN_PATH} ${BLD_PATH} ${DOC_PATH} ${INC_PATH} ${LIB_PATH}
	@${MAKE} -C ${ETC_PATH}
	@${MAKE} -C ${SRC_PATH}

.PHONY: test
test:
	@mkdir -p ${BLD_PATH}/test ${BIN_PATH}
	@${MAKE} -C ${SRC_PATH} test
	@${TEST_RUNNER}

.PHONY: run
run: ${EXE}
	@${EXE}

.PHONY: clean
clean:
	@rm -rf ${OUT_PATH} ${BIN_PATH} ${BLD_PATH} ${DOC_PATH} ${INC_PATH} ${LIB_PATH}
