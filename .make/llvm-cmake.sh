#!/bin/sh
set -e

mkdir -p ${LLVM_BUILD_PATH}
cd ${LLVM_PATH}
cmake ${LLVM_CMAKE_ARGS}
cd -
