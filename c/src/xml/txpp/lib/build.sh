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

echo "./configure --libdir=$TXPP_HOME/lib"
./configure --libdir=$TXPP_HOME/lib

echo "make"
make 2> txpp_build_errors

echo "make install"
make install

