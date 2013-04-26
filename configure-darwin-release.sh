#!/bin/sh

#---------------------------------------------------------------------------------
# Source and Install directories
#---------------------------------------------------------------------------------

export builddir=./build/release

# Installation directory.
# This must be specified in the format shown here
# or gcc won't be able to find it's libraries and includes
# if you move the installation.
export prefix=~/mapip2

#---------------------------------------------------------------------------------
# set the target and compiler flags
#---------------------------------------------------------------------------------

export CFLAGS='-O2 -pipe -Werror -I/opt/local/include'
export CXXFLAGS='-O2 -pipe -Werror'
export LDFLAGS='-L/opt/local/lib'
export DEBUG_FLAGS=''

export extra_configure_params='
	--with-gmp
	--with-gmp-include=/opt/local/include
	--with-gmp-lib=/opt/local/lib
'

./configure-common.sh
