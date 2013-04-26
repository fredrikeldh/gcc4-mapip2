#!/bin/sh

#---------------------------------------------------------------------------------
# Source and Install directories
#---------------------------------------------------------------------------------

export builddir=./build/debug

# Installation directory.
# This must be specified in the format shown here
# or gcc won't be able to find it's libraries and includes
# if you move the installation.
export prefix=/usr/mapip2

#---------------------------------------------------------------------------------
# set the target and compiler flags
#---------------------------------------------------------------------------------

export CFLAGS='-g -pipe -Werror'
export CXXFLAGS='-g -pipe -Werror'
export LDFLAGS=''
export DEBUG_FLAGS=''

./configure-common.sh
