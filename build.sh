#!/bin/bash

echo "----------------------------------"
echo "build server, client and samples"
echo "----------------------------------"
echo "clean previous build"
make distclean
echo "run libtoolize."          && 
libtoolize --force              && 
echo "run aclocal."             && 
aclocal                         && 
echo "run autoconf."            && 
autoconf                        && 
echo "run autoheader."          && 
autoheader                      && 
echo "run automake."            && 
automake --add-missing --gnu    &&

echo "configure --libdir=$AXISCPP_HOME/bin --bindir=$AXISCPP_HOME/bin"
./configure --libdir=$AXISCPP_HOME/bin --bindir=$AXISCPP_HOME/bin
echo "make"
make 2> build_errors
echo "make install"
make install

cd ${AXISCPP_HOME}/samples/server
make distclean
echo "building server samples"
sh build.sh

cd ${AXISCPP_HOME}/samples/client
make distclean
echo "building client samples"
sh build.sh

