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

echo "configure --prefix=$AXISCPP_DEPLOY --libdir=$AXISCPP_DEPLOY/lib --bindir=$AXISCPP_DEPLOY/bin"
./configure --prefix=$AXISCPP_DEPLOY \
    --libdir=$AXISCPP_DEPLOY/lib \
    --bindir=$AXISCPP_DEPLOY/bin \
    --enable-apache2=yes \
    --enable-apache=yes \
    --enable-expat=yes \
    --enable-xercesc=yes
echo "make"
make 2> build_errors
echo "make install"
make install

#cd ${AXISCPP_HOME}/samples/server
#echo "building server samples"
#sh build.sh

#cd ${AXISCPP_HOME}/samples/client
#echo "building client samples"
#sh build.sh

