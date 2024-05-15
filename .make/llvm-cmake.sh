#!/usr/bin/env zsh
set -e

LLVM_OUT_PATH="/home/opatterson/Repos/MrTreev/RayGame/out/sysroot"
LLVM_PATH="/home/opatterson/Repos/MrTreev/RayGame/ext/llvm-project"
LLVM_BUILD_PATH="${LLVM_PATH}/build"
LLVM_BUILD_TYPE="RelWithDebInfo"
rm -r "${LLVM_BUILD_PATH}"

cmake \
    -G Ninja \
    -S "${LLVM_PATH}/llvm" \
    -B "${LLVM_BUILD_PATH}" \
    -DCLANG_DEFAULT_RTLIB=compiler-rt \
    -DCMAKE_BUILD_TYPE="${LLVM_BUILD_TYPE}" \
    -DCMAKE_CXX_COMPILER="${LLVM_OUT_PATH}/bin/clang++" \
    -DCMAKE_CXX_STANDARD=20 \
    -DCMAKE_C_COMPILER="${LLVM_OUT_PATH}/bin/clang" \
    -DCMAKE_INSTALL_PREFIX="${LLVM_OUT_PATH}" \
    -DDEFAULT_SYSROOT="${LLVM_OUT_PATH}" \
    -DLLVM_ENABLE_LLVM_LIBC=ON \
    -DLLVM_ENABLE_PROJECTS="compiler-rt;cross-project-tests;clang;clang-tools-extra;libc;libclc;lld;lldb" \
    -DLLVM_ENABLE_RTTI=ON \
    -DLLVM_ENABLE_RUNTIMES="all" \
    -DLLVM_INSTALL_BINUTILS_SYMLINKS=ON \
    -DLLVM_INSTALL_UTILS=ON \
    -DLLVM_LIBC_FULL_BUILD=ON \
    -DLLVM_TARGETS_TO_BUILD=X86 \
    -Wno-deprecated \
    -Wno-dev

ninja -C "${LLVM_BUILD_PATH}"
# ninja -C "${LLVM_BUILD_PATH}" install
