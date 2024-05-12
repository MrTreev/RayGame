#!/usr/bin/env bash
set -e

LLVM_BUILD_PATH="/home/opatterson/Repos/MrTreev/RayGame/build"
OUT_PATH="/home/opatterson/Repos/MrTreev/RayGame/out/sysroot"
LLVM_PATH="/home/opatterson/Repos/MrTreev/RayGame/ext/llvm-project"

build_llvm="${LLVM_BUILD_PATH}/llvm"
build_libc="${LLVM_BUILD_PATH}/libc"
build_libcxx="${LLVM_BUILD_PATH}/libcxx"
mkdir -p "${build_llvm}" "${build_libc}" "${build_libcxx}"

llvm="${LLVM_PATH}"
install_prefix="${OUT_PATH}"
build_type="Debug"

cmake                                                                           \
    -G Ninja                                                                    \
    -S ${llvm}/llvm                                                             \
    -B ${build_llvm}                                                            \
    -DLLVM_INSTALL_UTILS=ON                                                     \
    -DCMAKE_INSTALL_PREFIX="${install_prefix}"                                  \
    -DCMAKE_BUILD_TYPE="${build_type}"
ninja -C "${build_llvm}" install

cmake                                                                           \
    -S ${llvm}/llvm                                                             \
    -B "${build_libc}"                                                          \
    -G Ninja                                                                    \
    -DCLANG_DEFAULT_LINKER=lld                                                  \
    -DCLANG_DEFAULT_RTLIB=compiler-rt                                           \
    -DCMAKE_BUILD_TYPE="${build_type}"                                          \
    -DCMAKE_CXX_COMPILER="${install_prefix}/bin/clang++"                        \
    -DCMAKE_C_COMPILER="${install_prefix}/bin/clang"                            \
    -DCMAKE_INSTALL_PREFIX="${install_prefix}"                                  \
    -DCOMPILER_RT_BUILD_GWP_ASAN=OFF                                            \
    -DCOMPILER_RT_BUILD_SCUDO_STANDALONE_WITH_LLVM_LIBC=ON                      \
    -DCOMPILER_RT_SCUDO_STANDALONE_BUILD_SHARED=OFF                             \
    -DDEFAULT_SYSROOT="${install_prefix}"                                       \
    -DLLVM_ENABLE_PROJECTS="clang;libc;lld;compiler-rt"                         \
    -DLLVM_EXTERNAL_LIT=${build_llvm}/utils/lit                                 \
    -DLLVM_LIBC_FULL_BUILD=ON                                                   \
    -DLLVM_LIBC_INCLUDE_SCUDO=ON                                                \
    -DLLVM_ROOT="${install_prefix}"                                             \
    -DLLVM_RUNTIME_TARGETS="x86_64-pc-linux-gnu"
ninja -C "${build_libc}" install

cmake                                                                           \
    -S "${llvm}/runtimes"                                                       \
    -G Ninja                                                                    \
    -B "${build_libcxx}"                                                        \
    -DCMAKE_BUILD_TYPE="${build_type}"                                          \
    -DCMAKE_INSTALL_PREFIX="${install_prefix}"                                  \
    -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind"                         \
    -DLLVM_RUNTIME_TARGETS="x86_64-pc-linux-gnu"
ninja -C "${build_libcxx}" install-runtimes
