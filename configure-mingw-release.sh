#!/bin/sh

# Note:
# Make sure the GCC source code has UNIX (LF) line endings.
# CRLF line endings will cause mysterious configuration bugs.

#---------------------------------------------------------------------------------
# Source and Install directories
#---------------------------------------------------------------------------------

builddir=./build/release

# The sourcecode dir for gcc,
# relative to the builddir.
# This must be specified in the format shown here
# as one of the tools built during the process will fail
# if absolute paths are specified.
# The example here assumes that the gcc source directory
# is at the same level as the script.
SRCDIR=../..

# Installation directory.
# This must be specified in the format shown here
# or gcc won't be able to find it's libraries and includes
# if you move the installation.
prefix=/usr/mapip2

#---------------------------------------------------------------------------------
# set the path for the installed binutils
#---------------------------------------------------------------------------------

#export PATH=${PATH}:/c/cross-gcc/mosync/bin

#---------------------------------------------------------------------------------
# set the target and compiler flags
#---------------------------------------------------------------------------------

target=mapip2
progpref=mapip2-

export CFLAGS='-O2 -pipe -Werror -Wno-unused-result'
export CXXFLAGS='-O2 -pipe -Werror -Wno-unused-result'
export LDFLAGS=''
export DEBUG_FLAGS=''

#---------------------------------------------------------------------------------
# build and install just the c compiler
#---------------------------------------------------------------------------------

mkdir -p $builddir
cd $builddir

$SRCDIR/configure \
	--enable-languages=c,c++ \
	--with-gcc --with-stabs \
	--disable-shared --disable-threads --disable-win32-registry --disable-nls \
	--prefix=$prefix \
	--target=$target \
	--without-headers \
	--program-prefix=$progpref -v \
	2>&1 | tee gcc_configure.log

mkdir -p gcc
touch gcc/insn-flags.h
make
