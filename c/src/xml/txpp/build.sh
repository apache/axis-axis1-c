#!/bin/bash
sh autogen.sh
echo "run configure"
./configure --prefix=/home/damitha/projects/inst_txpp \
             --enable-testcases=yes
echo "make"
make 2> build_errors
make install
