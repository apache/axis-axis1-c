#!/bin/bash
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

echo "./configure --bindir=$AXISCPP_HOME/tests/client/"
./configure --bindir=$AXISCPP_HOME/tests/client/

echo "make"
make 2> tests_build_errors

echo "make install"
make install

