include .make/config.mk

.PHONY: all
all: cmake

.PHONY: clean
clean:
	rm -rf ${CLEAN}
