#!/bin/bash

echo "----------------------------------"
echo "build server, client and samples"
echo "----------------------------------"

echo "run configure"
./configure --prefix=/usr/local/axiscpp_deploy \
    --libdir=/usr/local/axiscpp_deploy/lib \
    --bindir=/usr/local/axiscpp_deploy/bin \
    --with-apache2=/usr/local/apache2 \
    --with-apache=no \
    --with-expat=/usr/local/expat1957 \
    --with-xercesc=no \
    --enable-samples=yes \
    --enable-testcases=yes \
    --sysconfdir=/usr/local/axiscpp_deploy/conf
echo "make"
make 2> build_errors
echo "make install"
make install

