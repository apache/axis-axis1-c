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
    --enable-apache=no \
    --enable-expat=yes \
    --enable-xercesc=no \
    --enable-samples=yes \
    --enable-testcases=yes
echo "make"
make 2> build_errors
echo "make install"
make install

echo "Copy configuration files"
cp -f $AXISCPP_HOME/deploy/axiscpp.conf_linux $AXISCPP_DEPLOY/axiscpp.conf
cp -rf $AXISCPP_HOME/deploy/conf $AXISCPP_DEPLOY/
echo "Copy deploying files"
cp -f $AXISCPP_HOME/deploy/deploy_apache.sh $AXISCPP_DEPLOY/
cp -f $AXISCPP_HOME/deploy/deploy_apache2.sh $AXISCPP_DEPLOY/
echo "Copy the log directory"
cp -rf $AXISCPP_HOME/deploy/log $AXISCPP_DEPLOY/
