#!/bin/bash
sh autogen.sh
echo "run configure"
./configure --prefix=/home/damitha/projects/cvshead/src/xml/txpp/install
echo "make"
make 2> build_errors
make install
