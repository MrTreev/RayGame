COMPILER=clang
export COMPILER

include etc/make/config.mk

.PHONY: all
all: build

.PHONY: build
build: ${EXE}
${EXE}:
	@mkdir -p ${OUT_PATH} ${BIN_PATH} ${BLD_PATH} ${DOC_PATH} ${INC_PATH} ${LIB_PATH}
	${MAKE} -C ${ETC_PATH} all
	${MAKE} -C ${SRC_PATH} all

.PHONY: run
run: ${EXE}
	${EXE}

.PHONY: clean
clean:
	rm -rf ${OUT_PATH} ${BIN_PATH} ${BLD_PATH} ${DOC_PATH} ${INC_PATH} ${LIB_PATH}
