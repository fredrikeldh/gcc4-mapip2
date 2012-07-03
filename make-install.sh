#!/bin/bash

export mosyncSource=~/code/mosync-trunk

cd build/release/gcc && \
make && \
mkdir -p $MOSYNCDIR/mapip2/ && \
cp -uv xgcc $MOSYNCDIR/mapip2/ && \
mkdir -p $MOSYNCDIR/libexec/gcc/mapip2/4.6.3/ && \
cp -uv cpp $MOSYNCDIR/libexec/gcc/mapip2/4.6.3/ && \
cp -uv cc1 $MOSYNCDIR/libexec/gcc/mapip2/4.6.3/ && \
cp -uv cc1plus $MOSYNCDIR/libexec/gcc/mapip2/4.6.3/ && \
cd $mosyncSource && ./workfile.rb base && \
cd ~/code/binutils/binutils-mosync && ./workfile.rb && \
cd $mosyncSource && ./workfile.rb && \
cd $mosyncSource/examples/ && ./workfile.rb && \
true

#cd $mosyncSource && ./workfile.rb && \
#cd $mosyncSource/examples/ && ./workfile.rb && \

#cd $mosyncSource && ./workfile.rb more && \
#cd $mosyncSource/libs/ResCompiler && ./workfile.rb && \
#cd $mosyncSource/libs/MAStd && ./workfile.rb && \
#cd $mosyncSource/examples/cpp/3dLines && ./workfile.rb run && \

#./workfile.rb libs && \

#/home/fredrik/code/MoSync/mapip2/xgcc -o "build/mapip2_debug_4.6.3/crtlib.o" -std=gnu99 -g -O0 -fvisibility=hidden -I "/home/fredrik/code/MoSync/include" -Wall -Werror -Wextra -Wno-unused-parameter -Wwrite-strings -Wshadow -Wpointer-arith -Wundef -Wfloat-equal -Winit-self -Wmissing-noreturn -Wmissing-format-attribute -Wvariadic-macros -Wmissing-include-dirs -Wmissing-declarations -Wlogical-op -Wnested-externs -Wdeclaration-after-statement -Wstrict-prototypes -Wold-style-definition -Wmissing-prototypes -Wunreachable-code -Winline -DMOSYNCDEBUG -save-temps=obj -MMD -MF "build/mapip2_debug_4.6.3/crtlib.mft" -c "/home/fredrik/code/mosync-mapip2/libs/MAStd/crtlib.s" && \
#$MOSYNCDIR/libexec/gcc/mapip2/4.6.3/objdump -dr build/mapip2_debug_4.6.3/crtlib.o && \
#$MOSYNCDIR/libexec/gcc/mapip2/4.6.3/objdump -dr build/mapip2_debug_4.6.3/program && \
