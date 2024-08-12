include make/config.mk

.PHONY: all
all: build

.PHONY: build
build: ${EXE}
${EXE}:
	cd ${SRC_PATH} && ${MAKE} ${EXE}

.PHONY: run
run: ${EXE}
	${EXE}

.PHONY: clean
clean:
	rm -rf ${CLEAN}
