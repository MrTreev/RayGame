#!/bin/sh
set -ex

PATH_TOOLCHAINS=/home/opatterson/Repos/MrTreev/RayGame/toolchains
PATH_SOURCES=${PATH_TOOLCHAINS}/src
PATH_SYSROOT=${PATH_TOOLCHAINS}/gcc
PATH_BUILDS=${PATH_TOOLCHAINS}/build
THREAD_COUNT=32

log(){
    printf "\033[34m%s\033[0m\n" "$@" >&2;
};
log_red(){
    printf "\033[31m%s\033[0m\n" "$@" >&2;
};
log_green(){
    printf "\033[32m%s\033[0m\n" "$@" >&2;
};
check_cd(){
    cd "${1}" \
        || {
            log_red "Failed ($?) to CD into $1";
            exit 2;
        };
}
shallowclone(){
    git clone \
        --depth 1 \
        --recurse-submodules \
        --single-branch \
        --branch "$1" \
        "$2";
}

check_cd ${PATH_SOURCES}

[ -d ${PATH_SOURCES}/gcc ] \
	|| shallowclone "trunk" "https://gcc.gnu.org/git/gcc.git";
[ -d ${PATH_SOURCES}/glibc ] \
	|| {
		wget 'https://mirror.freedif.org/GNU/glibc/glibc-2.43.tar.xz';
		tar -xf glibc-2.43.tar.xz;
		mv glibc-2.43 glibc
	};
[ -d ${PATH_SOURCES}/binutils-gdb ] \
	|| shallowclone "master" "https://sourceware.org/git/binutils-gdb.git";

################################################################################
# Linux Headers
################################################################################
[ -e ${PATH_TOOLCHAINS}/gcc/include/linux ] || {
    cd ${PATH_SOURCES}/linux
    make ARCH=x86_64 INSTALL_HDR_PATH=${PATH_SYSROOT} headers_install
}

################################################################################
# binutils
################################################################################
[ -e ${PATH_TOOLCHAINS}/gcc/bin/addr2line ] || {
    mkdir -p ${PATH_BUILDS}/binutils-gdb;
	check_cd ${PATH_BUILDS}/binutils-gdb;
	${PATH_SOURCES}/binutils-gdb/configure \
		--srcdir=${PATH_SOURCES}/binutils-gdb \
        --prefix=${PATH_SYSROOT} \
		--enable-gold=yes \
		--enable-ld=yes \
		--enable-libada \
		--enable-libgm2 \
		--enable-libssp \
		--enable-libstdcxx \
		--enable-lto \
		--enable-vtable-verify \
		;
	make -j"${THREAD_COUNT}";
	make install;
	check_cd ${PATH_SOURCES};
}

################################################################################
# GCC
################################################################################
[ -e ${PATH_BUILDS}/gcc ] || {
    mkdir -p ${PATH_BUILDS}/gcc;
	check_cd ${PATH_BUILDS}/gcc;
	${PATH_SOURCES}/gcc/configure \
        --srcdir=${PATH_SOURCES}/gcc \
        --prefix=${PATH_SYSROOT} \
		--enable-gold=yes \
		--enable-ld=yes \
		--enable-libada \
		--enable-libgm2 \
		--enable-libssp \
		--enable-libstdcxx \
		--enable-lto \
		--enable-vtable-verify \
		;
	make -j"${THREAD_COUNT}";
	make install;
	check_cd ${PATH_SOURCES};
}

################################################################################
# glibc
################################################################################
[ -e ${PATH_TOOLCHAINS}/gcc/lib/libc.so ] || {
    mkdir -p ${PATH_BUILDS}/glibc;
	check_cd ${PATH_BUILDS}/glibc;
	${PATH_SOURCES}/glibc/configure \
		--srcdir=${PATH_SOURCES}/glibc \
        --prefix=${PATH_SYSROOT} \
        --with-sysroot=${PATH_SYSROOT} \
		--enable-libstdcxx \
		--enable-lto \
		--disable-werror \
		--disable-multi-arch \
        --with-binutils=${PATH_SYSROOT} \
        --with-headers=${PATH_SYSROOT}/include/linux \
        CC=${PATH_SYSROOT}/bin/gcc \
        CXX=${PATH_SYSROOT}/bin/g++ \
		;
	make -j"${THREAD_COUNT}";
	make install;
	check_cd ${PATH_SOURCES};
}
