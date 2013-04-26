#!/bin/sh

#---------------------------------------------------------------------------------
# Source and Install directories
#---------------------------------------------------------------------------------

export builddir=./build/release

# Installation directory.
# This must be specified in the format shown here
# or gcc won't be able to find it's libraries and includes
# if you move the installation.
export prefix=/usr/mapip2

#---------------------------------------------------------------------------------
# set the target and compiler flags
#---------------------------------------------------------------------------------

export CFLAGS='-O2 -pipe -Werror -Wno-unused-result'
export CXXFLAGS='-O2 -pipe -Werror -Wno-unused-result'
export LDFLAGS=''
export DEBUG_FLAGS=''

./configure-common.sh
