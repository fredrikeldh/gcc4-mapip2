#!/bin/sh

# Warning: Remove all .exe files from builddir before running this script.
# g++.exe (and possibly gcc.exe) will take over, breaking the configuration.
# Example error message: "WARNING: C++ preprocessor "g++ -E" fails sanity check"

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

export CFLAGS='-O2 -pipe -Werror -Wno-unused-result -Wno-pedantic-ms-format'
export CXXFLAGS='-O2 -pipe -Werror -Wno-unused-result -Wno-pedantic-ms-format'
export LDFLAGS=''
export DEBUG_FLAGS=''

./configure-common.sh
