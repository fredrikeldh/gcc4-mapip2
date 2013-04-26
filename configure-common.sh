
# Note:
# Make sure the GCC source code has UNIX (LF) line endings.
# CRLF line endings will cause mysterious configuration bugs.

export target=mapip2
export progpref=mapip2-

# The sourcecode dir for gcc,
# relative to the builddir.
# This must be specified in the format shown here
# as one of the tools built during the process will fail
# if absolute paths are specified.
# The example here assumes that the gcc source directory
# is at the same level as the script.
export SRCDIR=../..

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
	--with-bugurl=http://www.mosync.com/ \
	$extra_configure_params \
	2>&1 | tee gcc_configure.log

mkdir -p gcc
touch gcc/insn-flags.h
make all-gcc
