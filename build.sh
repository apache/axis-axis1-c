#!/bin/bash

echo "----------------------------------"
echo "build server, client and samples"
echo "----------------------------------"

echo "run configure"
./configure --prefix=/usr/local/axiscpp_deploy \
    --with-apache2=/usr/local/apache2 \
    --with-expat=/usr/local/expat1957
echo "make"
make 2> build_errors
echo "make install"
make install

