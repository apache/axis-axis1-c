#!/bin/bash

echo "----------------------------------"
echo "build server, client and samples"
echo "----------------------------------"
echo "clean previous build"
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

echo "run configure"
./configure --prefix=$AXISCPP_DEPLOY \
    --libdir=$AXISCPP_DEPLOY/lib \
    --bindir=$AXISCPP_DEPLOY/bin \
    --enable-apache2=yes \
    --enable-apache=no \
    --enable-expat=yes \
    --enable-xercesc=no \
    --enable-samples=yes \
    --enable-testcases=yes
echo "make"
make 2> build_errors
echo "make install"
make install

